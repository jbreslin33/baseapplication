//header
#include "network.h"

//log
#include "../tdreamsock/dreamSockLog.h"

//game
#include "../game/game.h"

//command
#include "../command/command.h"

//parser
#include "../parser/parser.h"

//byteBuffer
#include "../byteBuffer/byteBuffer.h"

//sockets
#ifdef WIN32
#include "../tdreamsock/dreamWinSock.h"
#else
#include "../tdreamsock/dreamLinuxSock.h"
#endif



#ifdef WIN32
//do nothing
#else
#include <stdio.h>
#include <memory.h>
#include <malloc.h>
#include <errno.h>
#include <unistd.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <signal.h>

#endif

Network::Network(Game* game, const char serverIP[32], int serverPort )
{
	//game
	mGame = game;

	//command
	mCommandToServer     = new Command(); 
	mLastCommandToServer = new Command();

	//parser
	mParser = new Parser();

	//server address
	mServerIP = serverIP;
	mServerPort = serverPort;

	//sequences
	mOutgoingSequence		= 1;
	mIncomingSequence		= 0;

#ifdef WIN32
	mDreamWinSock = new DreamWinSock();
#else
	mDreamLinuxSock = new DreamLinuxSock();
#endif

	mSocket = open();

	if(mSocket == DREAMSOCK_INVALID_SOCKET)
	{
		LogString("ERROR IN CONSTRUCTOR OF SERVER, INVALID SOCKET");
	}

	setSendToAddress(mServerIP,mServerPort);

	//parse
	mIncomingSequence = 0;
	mDroppedPackets = 0;

	//LogString("Server's information: IP address: %s, port: %d", mServerIP, mServerPort);
}

Network::~Network()
{
}

//open
SOCKET Network::open()
{
	SOCKET sock;

	struct sockaddr_in address;

	sock = createSocket(DREAMSOCK_UDP);

	if(sock == DREAMSOCK_INVALID_SOCKET)
		return sock;

	setNonBlocking(1);

	LogString("No net interface given, using any interface available");
	address.sin_addr.s_addr = htonl(INADDR_ANY);

	LogString("No port defined, picking one for you");
	address.sin_port = 0;

	address.sin_family = AF_INET;

	// Bind the address to the socket
	if(bind(sock, (struct sockaddr *) &address, sizeof(address)) == -1)
	{
#ifdef WIN32
		errno = WSAGetLastError();
		size_t t = 256;
		LogString("Error code %d: bind() : %s", errno, strerror_s("error",t,errno));
#else
		LogString("Error code %d: bind() : %s", errno, strerror(errno));
#endif

		return DREAMSOCK_INVALID_SOCKET;
	}

	// Get the port number (if we did not define one, we get the assigned port number here)
	socklen_t len = sizeof(address);
	getsockname(sock, (struct sockaddr *) &address, &len);

	LogString("Opening UDP port = %d", ntohs(address.sin_port));

	return sock;
}


SOCKET Network::createSocket(int protocol)
{
	int type;
	int proto;

	// Check which protocol to use
	if(protocol == DREAMSOCK_TCP)
	{
		type = SOCK_STREAM;
		proto = IPPROTO_TCP;
	}
	else
	{
		type = SOCK_DGRAM;
		proto = IPPROTO_UDP;
	}

	// Create the socket
	if((mSocket = socket(AF_INET, type, proto)) == -1)
	{
		LogString("createSocket - socket() failed");

#ifdef WIN32
		errno = WSAGetLastError();
		size_t t = 256;
		LogString("Error: socket() code %d : %s", errno, strerror_s("error",t,errno));
#else
		LogString("Error: socket() : %s", strerror(errno));
#endif

		return DREAMSOCK_INVALID_SOCKET;
	}

	return mSocket;
}

int Network::setNonBlocking(u_long setMode)
{
	u_long set = setMode;

	// Set the socket option
#ifdef WIN32
	return ioctlsocket(mSocket, FIONBIO, &set);
#else
	return ioctl(mSocket, FIONBIO, &set);
#endif
}

//close
void Network::close()
{
#ifdef WIN32
		closesocket(mSocket);
#else
		close(mSocket);
#endif
}

//send
void Network::send(ByteBuffer* byteBuffer)
{
	send(byteBuffer->mSize,byteBuffer->mCharArray,*(struct sockaddr *) &sendToAddress);
	
	byteBuffer->BeginReading();
	int type = byteBuffer->ReadByte();

	if(type > 0)
	{
		mOutgoingSequence++;
	}
}

void Network::send(int length, char *data,  struct sockaddr addr)
{
	int	ret;

	ret = sendto(mSocket, data, length, 0, &addr, sizeof(addr));

	if(ret == -1)
	{
#ifdef WIN32
		errno = WSAGetLastError();

		// Silently handle wouldblock
		if(errno == WSAEWOULDBLOCK)
			return;
		size_t t = 256;
		LogString("Error code %d: sendto() : %s", errno, strerror_s("error",t,errno));
#else
		// Silently handle wouldblock
		if(errno == EWOULDBLOCK)
			return;

		LogString("Error code %d: sendto() : %s", errno, strerror(errno));
#endif
	}
}

void Network::setSendToAddress(const char* serverIP, int serverPort)
{
	//ripped from client, since we only have one client on this side let's do it here.
	memset((char *) &sendToAddress, 0, sizeof(sendToAddress));

	u_long inetAddr               = inet_addr(serverIP);
	sendToAddress.sin_port        = htons((u_short) serverPort);
	sendToAddress.sin_family      = AF_INET;
	sendToAddress.sin_addr.s_addr = inetAddr;
}

//receive
int Network::checkForByteBuffer(ByteBuffer* byteBuffer)
{
	char* data = byteBuffer->mCharArray;

	int ret;
	struct sockaddr tempFrom;
	socklen_t fromlen;

	fromlen = sizeof(tempFrom);

	ret = recvfrom(mSocket, data, 1400, 0, (struct sockaddr *) &tempFrom, &fromlen);

	if(ret <= 0)
		return 0;

	// Parse system messages
	parsePacket(byteBuffer);

	if(ret == -1)
	{
#ifdef WIN32
		errno = WSAGetLastError();

		// Silently handle wouldblock
		if(errno == WSAEWOULDBLOCK)
			return ret;

		if(errno == WSAEMSGSIZE)
		{
			// ERROR: Oversize packet

			return ret;
		}
		size_t t = 256;

		LogString("Error code %d: recvfrom() : %s", errno, strerror_s("error",t,errno));
#else
		// Silently handle wouldblock
		if(errno == EWOULDBLOCK || errno == ECONNREFUSED)
			return ret;

		LogString("Error code %d: recvfrom() : %s", errno, strerror(errno));
#endif

		return ret;
	}

	byteBuffer->SetSize(ret);

	return ret;
}

//i feel like network should handle out of sequence packet warnings...
void Network::parsePacket(ByteBuffer *mes)
{
	mes->BeginReading();
	int type = mes->ReadByte();

	// Check if the type is a positive number
	// = is the packet sequenced
	if(type > 0)
	{
		signed short sequence		= mes->ReadShort();

		if(sequence <= mIncomingSequence)
		{
			LogString("Client: (sequence: %d <= incoming seq: %d)",
				sequence, mIncomingSequence);

			LogString("Client: Sequence mismatch");
		}

		mDroppedPackets = sequence - mIncomingSequence + 1;

		mIncomingSequence = sequence;
	}
}

void Network::reset(void)
{
    mOutgoingSequence                = 1;
    mIncomingSequence                = 0;
}


/***************************************************
*			CONNECT
***************************************************/
void Network::sendConnect()
{
	ByteBuffer* byteBuffer = new ByteBuffer();
	byteBuffer->WriteByte(mParser->mMessageConnect);
	send(byteBuffer);
}

/***************************************************
*			DISCONNECT
***************************************************/
void Network::sendDisconnect()
{
	ByteBuffer* byteBuffer = new ByteBuffer();
	byteBuffer->WriteByte(mParser->mMessageDisconnect);
	send(byteBuffer);
	reset();
}

/***************************************************
*			COMMAND
***************************************************/

void Network::sendCommand(void)
{
	//create byteBuffer
	ByteBuffer* byteBuffer = new ByteBuffer();

	//WRITE: type
	byteBuffer->WriteByte(mParser->mMessageFrame);					
	
	//WRITE: sequence
	byteBuffer->WriteShort(mOutgoingSequence);

	// Build delta-compressed move command
	int flags = 0;

	// Check what needs to be updated
	if(mLastCommandToServer->mKey != mCommandToServer->mKey)
	{
		flags |= mParser->mCommandKey;
	}

	if(mLastCommandToServer->mMilliseconds != mCommandToServer->mMilliseconds)
	{
		flags |= mParser->mCommandMilliseconds;
	}
	
	// Add to the message
	byteBuffer->WriteByte(flags);

	if(flags & mParser->mCommandKey)
	{
		//WRITE: key
		byteBuffer->WriteByte(mCommandToServer->mKey);
	}

	if(flags & mParser->mCommandMilliseconds)
	{
		//WRITE: milliseconds
		byteBuffer->WriteByte(mCommandToServer->mMilliseconds);
	}
	
	//set 'last' commands for diff
	mLastCommandToServer->mKey = mCommandToServer->mKey;
	mLastCommandToServer->mMilliseconds = mCommandToServer->mMilliseconds;

	// Send the packet
	send(byteBuffer);
}

/***************************************************
*			PACKETS
***************************************************/
void Network::readPackets()
{
	int type;
	int ret;

	ByteBuffer* byteBuffer = new ByteBuffer();

	while(ret = checkForByteBuffer(byteBuffer))
	{
		byteBuffer->BeginReading();

		type = byteBuffer->ReadByte();

		switch(type)
		{
			case mParser->mMessageAddShape:
				mGame->addShape(true,byteBuffer);
			break;

			case mParser->mMessageRemoveShape:
				mGame->removeShape(byteBuffer);
			break;

			case mParser->mMessageFrame:
				mGame->readServerTick(byteBuffer);
			break;

			case mParser->mMessageServerExit:
				mGame->shutdown();
			break;
		}
	}
}