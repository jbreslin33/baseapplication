//parent
#include "server.h"

//log
#include "../tdreamsock/dreamSockLog.h"

//network
#include "../network/network.h"

//client
#include "../client/client.h"

//message
#include "../message/message.h"

//shape
#include "../shape/shape.h"

//game
#include "../game/game.h"

Server::Server(Game* serverSideGame,const char *localIP, int serverPort)
{
	init			= false;
	mGame = serverSideGame;
	mLocalIP = localIP;
	
	// Store the server IP and port for later use
	port = serverPort;

	// Create network
	mNetwork = new Network(localIP, port);

	init = true;
}

Server::~Server()
{
	mClientVector.empty();
	mNetwork->dreamSock_CloseSocket(mNetwork->mSocket);
}

void Server::createClient(struct sockaddr *address)
{
	Client* client = new Client(this, address);
	
	client->createShape();
	//let this client know about all shapes(it will sending add for it's avatar as that is done right above.)
	client->sendAllShapes();
}

void Server::addClient(Client* client)
{
	mClientVector.push_back(client);
}

void Server::sendRemoveShape(Shape* shape)
{
	
	int index = shape->mIndex;

	// Send 'DREAMSOCK_MES_REMOVESHAPE' message to every client
	for (unsigned int i = 0; i < mClientVector.size(); i++)
	{
		mClientVector.at(i)->mMessage.Init(mClientVector.at(i)->mMessage.outgoingData,
			sizeof(mClientVector.at(i)->mMessage.outgoingData));

		mClientVector.at(i)->mMessage.WriteByte(mRemoveShape);	// type
		mClientVector.at(i)->mMessage.WriteByte(index);							// index
	}
	sendPackets();
}

void Server::parsePacket(Message *mes, struct sockaddr *address)
{
	mes->BeginReading();

	int type = mes->ReadByte();

	if (type == mConnect)
	{
		createClient(address);
		//LogString("LIBRARY: Server: a client connected succesfully");
	}
	else
	{
		// Find the correct client by comparing addresses
		for (unsigned int i = 0; i < mClientVector.size(); i++)
		{
			if(memcmp(mClientVector.at(i)->GetSocketAddress(), address, sizeof(address)) == 0)
			{
				mClientVector.at(i)->mLastMessageTime = mNetwork->dreamSock_GetCurrentSystemTime();

				// Check if the type is a positive number
				// -> is the packet sequenced
				if(type > 0)
				{
					signed short sequence         = mes->ReadShort();

					if(sequence <= mClientVector.at(i)->mIncomingSequence)
					{
						LogString("LIB: Server: Sequence mismatch (sequence: %ld <= incoming seq: %ld)",
						sequence, mClientVector.at(i)->mIncomingSequence);
					}

					mClientVector.at(i)->mDroppedPackets  = sequence - mClientVector.at(i)->mIncomingSequence - 1;
					//set mIncomingSequence to current one that just came in for next time comparison...
					mClientVector.at(i)->mIncomingSequence = sequence;
				}

				// Wait for one message before setting state to connected
				if(mClientVector.at(i)->mConnectionState == DREAMSOCK_CONNECTING)
				{
					mClientVector.at(i)->mConnectionState = DREAMSOCK_CONNECTED;
				}

				// Parse through the system messages
				switch(type)
				{
					case mDisconnect:
						mClientVector.at(i)->remove();
						LogString("LIBRARY: Server: a client disconnected");
						break;
				}
			}
		}
	}
}

int Server::checkForTimeout(char *data, struct sockaddr *from)
{
	int currentTime = mNetwork->dreamSock_GetCurrentSystemTime();

	for (unsigned int i = 0; i < mClientVector.size(); i++)
	{
		// Don't timeout when connecting
		if(mClientVector.at(i)->mConnectionState == DREAMSOCK_CONNECTING)
		{
			continue;
		}

		// Check if the client has been silent for 30 seconds
		// If yes, assume crashed and remove the client
		if(currentTime - mClientVector.at(i)->mLastMessageTime > 30000)
		{
			LogString("Client timeout, disconnecting (%d - %d = %d)",
				currentTime, mClientVector.at(i)->mLastMessageTime, currentTime - mClientVector.at(i)->mLastMessageTime);

			// Build a 'fake' message so the applicationBreslin will also
			// receive notification of a client disconnecting
			Message mes;
			mes.Init(data, sizeof(data));
			mes.WriteByte(mDisconnect);

			mClientVector.at(i)->remove();

			return mes.GetSize();
		}
	}
	return 0;
}

int Server::getPacket(char *data, struct sockaddr *from)
{
	// Check if the server is set up
	if(!mNetwork->mSocket)
		return 0;

	// Check for timeout
	int timeout = checkForTimeout(data, from);

	if(timeout)
		return timeout;

	// Wait for a while or incoming data
	int maxfd = mNetwork->mSocket;
	fd_set allset;
	struct timeval waittime;

	waittime.tv_sec = 10 / 1000;
	waittime.tv_usec = (10 % 1000) * 1000;

	FD_ZERO(&allset); 
	FD_SET(mNetwork->mSocket, &allset);

	fd_set reading = allset;

	int nready = select(maxfd + 1, &reading, NULL, NULL, &waittime);

	if(!nready)
		return 0;

	// Read data of the socket
	int ret = 0;

	Message mes;
	mes.Init(data, sizeof(data));

	ret = mNetwork->dreamSock_GetPacket(mNetwork->mSocket, mes.data, from);

	if(ret <= 0)
		return 0;

	mes.SetSize(ret);

	// Parse system messages
	parsePacket(&mes, from);

	return ret;
}

//this loops thru each client instance and then calls their sendPacket(mess) function
void Server::sendPackets()
{
	// Check if the server is set up
	if(!mNetwork->mSocket)
		return;

	for (unsigned int i = 0; i < mClientVector.size(); i++)
	{
		if(mClientVector.at(i)->mMessage.GetSize() == 0)
			continue;

		mClientVector.at(i)->SendPacket(&mClientVector.at(i)->mMessage);
	}
}

void Server::readPackets()
{
	char data[1400];

	int type;
	int ret;

	struct sockaddr address;

	Message mes;
	mes.Init(data, sizeof(data));

	// Get the packet from the socket
	try
	{
		while(ret = getPacket(mes.data, &address))
		{
			mes.SetSize(ret);
			mes.BeginReading();

			type = mes.ReadByte();
			
			// Check the type of the message
			switch(type)
			{
			case mConnect:

				break;

			case mDisconnect:

				for (unsigned int i = 0; i < mClientVector.size(); i++)
				{
					if(memcmp(&mClientVector.at(i)->mMyaddress, &address, sizeof(address)) == 0)
					{
						//don't know why i don't do anything here i assume that I am just using
						//checkForTimeout fallback.	
					}
				}
				break;

			case mMessageFrame:
				// Skip sequences
				signed short seq = mes.ReadShort();
				
				//let's try this with shapes instead.....
				for (unsigned int i = 0; i < mGame->mShapeVector.size(); i++)
				{
					if (mGame->mShapeVector.at(i)->mClient != NULL)
					{
						if(memcmp(&mGame->mShapeVector.at(i)->mClient->mMyaddress, &address, sizeof(address)) == 0)
						{
							mGame->readDeltaMoveCommand(&mes, mGame->mShapeVector.at(i)->mClient);
							break;
						}
					}
				}
				break;
			}
		}
	}
	catch(...)
	{
		LogString("Unknown Exception caught in Lobby ReadPackets loop");

#ifdef WIN32
		MessageBox(NULL, "Unknown Exception caught in Lobby ReadPackets loop", "Error", MB_OK | MB_TASKMODAL);
#endif
	}
}
