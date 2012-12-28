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

//postgresql
#include <stdio.h>
#include <postgresql/libpq-fe.h>

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
	LogString("type:%d",type);
	//signed short sequence         = mes->ReadShort();
	int sequence         = mes->ReadByte();
	LogString("sequence:%d",sequence);
	
	if (type == mConnect)
	{
		createClient(address);
		LogString("LIBRARY: Server: a client connected succesfully");
	}
	else
	{
		// Find the correct client by comparing addresses
		for (unsigned int i = 0; i < mClientVector.size(); i++)
		{
		//	LogString("sa_family:%d",address->sa_family);
		//	LogString("sa_data 0:%d 1:%d 2:%d 3:%d, 4:%d, 5:%d 6:%d 7:%d 8:%d 9:%d 10:%d 11:%d 12:%d 13:%d",address->sa_data[0],address->sa_data[1], address->sa_data[2], address->sa_data[3], address->sa_data[4], address->sa_data[5], address->sa_data[6], address->sa_data[7], address->sa_data[8], address->sa_data[9], address->sa_data[10], address->sa_data[11], address->sa_data[11], address->sa_data[12], address->sa_data[13]);
//inet_ntoa((struct sockaddr_in)saddr.sin_addr))
			if(memcmp(mClientVector.at(i)->GetSocketAddress(), address, sizeof(address)) == 0)
			{
				LogString("memcmp == true");
				mClientVector.at(i)->mLastMessageTime = mNetwork->dreamSock_GetCurrentSystemTime();

				// Check if the type is a positive number
				// -> is the packet sequenced
				if(type > 0)
				{
					signed short sequence         = mes->ReadShort();
					LogString("sequence:%d",sequence);

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
	{	
		return 0;
	}

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

void Server::readDB()
{
        PGconn          *conn;
        PGresult        *res;
        int             rec_count;
        int             row;
        int             col;
        conn = PQconnectdb("dbname=abcandyou host=localhost user=postgres password=mibesfat");
        res = PQexec(conn,
       "select * from users");
        if (PQresultStatus(res) != PGRES_TUPLES_OK)
        {
                puts("We did not get any data!");
                //exit(0);
        }
        rec_count = PQntuples(res);
/*
        printf("We received %d records.\n", rec_count);
        puts("==========================");
        for (row=0; row<rec_count; row++)
        {
                for (col=0; col<3; col++)
                {
                        printf("%s\t", PQgetvalue(res, row, col));
                }
                puts("");
        }

        puts("==========================");
*/
        PQclear(res);

        PQfinish(conn);

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
			//LogString("type:%d",type);
			
			// Check the type of the message
			switch(type)
			{
			case mMessageFrame:
				// Skip sequences
				signed short seq = mes.ReadShort();
				//LogString("seq:%d",seq);
				
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
