#include "client.h"
#include "../tdreamsock/dreamSockLog.h"

#include "../../serverside/network/network.h"
#include "../../serverside/server/server.h"
#ifdef WIN32
//
#else
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#endif

//server side client constructor, many instances will be made, one for each client connected.
Client::Client(Server* server, struct sockaddr *address)
{
	mServer = server;

	mShape = NULL; //to be filled when we actually create the shape

	mLastMessageTime		= 0;

	mServer->mClientVector.push_back(this);

	SetSocketAddress(address);

	mConnectionState = DREAMSOCK_CONNECTING;
	mOutgoingSequence = 1;
	mIncomingSequence = 0;

	//memcpy(&mMyaddress,GetSocketAddress(), sizeof(struct sockaddr));
}

Client::~Client()
{
	mServer->mNetwork->dreamSock_CloseSocket(mServer->mNetwork->mSocket);
	//delete mNetwork;
}

void Client::SendPacket(Message *theMes)
{
	// Check that everything is set up
	if(!mServer->mNetwork->mSocket || mConnectionState == DREAMSOCK_DISCONNECTED)
	{
		LogString("SendPacket error: Could not send because the client is disconnected");
		return;
	}

	// If the message overflowed do not send it
	if(theMes->GetOverFlow())
	{
		LogString("SendPacket error: Could not send because the buffer overflowed");
		return;
	}

	mServer->mNetwork->dreamSock_SendPacket(mServer->mNetwork->mSocket, theMes->GetSize(), theMes->data, mMyaddress);

	// Check if the packet is sequenced
	theMes->BeginReading();
	int type = theMes->ReadByte();

	if(type > 0)
	{
		mOutgoingSequence++;
	}
}


