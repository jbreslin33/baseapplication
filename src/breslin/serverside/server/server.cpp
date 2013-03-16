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

	readDB();
}

Server::~Server()
{
	mClientVector.empty();
	mNetwork->dreamSock_CloseSocket(mNetwork->mSocket);
}

//for c++ and java
void Server::createClient(struct sockaddr *address)
{
/*
	//let this client know about all shapes(it will sending add for it's avatar as that is done right above.)
	client->sendAllShapes();
	
	//create the shape for this client at that point we send this shape to all clients	
	client->createShape();
*/
}

//browser
void Server::createClient(struct sockaddr * address, int clientID)
{
	Client* client = new Client(this, address, clientID);

	//give this client all current shapes	
	//for this first client this should no times for the 2nd once.
	client->sendAllShapesBrowser();

	//create the shape for this client at that point we send this shape to all clients	
	if (clientID != -1)
	{	
		client->createShape();
	}
	
	// that's that as we cannot communicate back to the browser from here..unless this is where we change db or whatever medium we will use to communicate with browser.
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
		mMessage.Init(mMessage.outgoingData,
			sizeof(mMessage.outgoingData));

		mMessage.WriteByte(mRemoveShape);	// type
		mMessage.WriteByte(index);		// index
	}
	sendPackets();

}

void Server::parsePacket(Message *mes, struct sockaddr *address)
{
	Client* client;
	mes->BeginReading();

	int type = mes->ReadByte();
	
	if (type == mConnect)
	{
		//createClient(address);
		Client* client = new Client(this, address);
		LogString("connected c++ client!!!!!!!!!!!!");
	}
	
	else if (type == mConnectNode)
	{
		int clientID = mes->ReadByte();

		createClient(address,-1);

	}	

	else if (type == mConnectBrowser)
	{
		int clientID = mes->ReadByte();

		createClient(address,clientID);

	}

	else if (type == mJoinGame)
	{
		for (unsigned int i = 0; i < mClientVector.size(); i++)
		{
			if( memcmp(mClientVector.at(i)->GetSocketAddress(), address, sizeof(address)) == 0)
			{
				client = mClientVector.at(i);
				//let this client know about all shapes
				client->sendAllShapes();
	
				//create the shape for this client at that point we send this shape to all clients	
				client->createShape();
			}
		}
	}
	
	else if (type == mJoinGameBrowser)
	{

	}
	
	else if (type == mQuitGame)
	{
		// Find the correct client by comparing addresses
		for (unsigned int i = 0; i < mClientVector.size(); i++)
		{
			if( memcmp(mClientVector.at(i)->GetSocketAddress(), address, sizeof(address)) == 0)
			{
				client = mClientVector.at(i);
				checkClientQuitGame(type,client,mes);
			}
		}
	}

	else if (type == mQuitGameBrowser)
	{

	}


	else if (type == mMessageFrame || type == mDisconnect)
	{
		// Find the correct client by comparing addresses
		for (unsigned int i = 0; i < mClientVector.size(); i++)
		{
			if( memcmp(mClientVector.at(i)->GetSocketAddress(), address, sizeof(address)) == 0)
			{
				client = mClientVector.at(i);
				checkClientQuit(type,client,mes);
			}
		}
	}

	else if (type == mMessageFrameBrowser ||  type == mDisconnectBrowser)
	{
		int clientID = mes->ReadByte();
		
		for (unsigned int i = 0; i < mClientVector.size(); i++)
		{
			if (mClientVector.at(i)->mClientID == clientID)
			{
				client = mClientVector.at(i);
				checkClientQuit(type,client,mes);
			}
		}

	} 
}

void Server::checkClientQuitGame(int type, Client* client, Message* mes)
{
	if (type == mQuitGame || type == mQuitGameBrowser)
	{
		if (client->mShape)
		{
			client->mShape->remove();
		}
               	LogString("LIBRARY: Server: a client disconnected");
                return;
	}
	/*
	client->mLastMessageTime = mNetwork->dreamSock_GetCurrentSystemTime();

       	// Wait for one message before setting state to connected
       	if(client->mConnectionState == DREAMSOCK_CONNECTING)
       	{
       		client->mConnectionState = DREAMSOCK_CONNECTED;
	}
*/
}

void Server::checkClientQuit(int type, Client* client, Message* mes)
{
	if (type == mDisconnect || type == mDisconnectBrowser)
	{
		client->remove();
               	LogString("LIBRARY: Server: a client disconnected");
                return;
	}
	client->mLastMessageTime = mNetwork->dreamSock_GetCurrentSystemTime();

       	// Wait for one message before setting state to connected
       	if(client->mConnectionState == DREAMSOCK_CONNECTING)
       	{
       		client->mConnectionState = DREAMSOCK_CONNECTED;
	}
}

int Server::checkForTimeout()
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
			//Message mes;
			//mes.Init(data, sizeof(data));
			//mes.WriteByte(mDisconnect);

			mClientVector.at(i)->remove();

			//return mes.GetSize();
		}
	}
	return 0;
}

int Server::getPacket(char *data, struct sockaddr *from)
{
	// Check if the server is set up
	if(!mNetwork->mSocket)
		return 0;

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
//we are right here I need to just send to one client for all browsers then he should broadcast
void Server::sendPackets()
{
	// Check if the server is set up
	if(!mNetwork->mSocket)
		return;

	for (unsigned int i = 0; i < mClientVector.size(); i++)
	{
		if(mMessage.GetSize() == 0)
			continue;

		//is the a browser client but not THE browser client which is -1 normal c++ clients are 0 if so skip
		if(mClientVector.at(i)->mClientID > 0)
			continue; 

		mClientVector.at(i)->SendPacket(&mMessage);
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
       "select * from schools");
        if (PQresultStatus(res) != PGRES_TUPLES_OK)
        {
                puts("We did not get any data!");
                //exit(0);
        }
        rec_count = PQntuples(res);
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

			// Check the type of the message
			switch(type)
			{
			case mMessageFrame:
				
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
		 	
			case mMessageFrameBrowser:
				//grab clientID
				int clientID = mes.ReadByte();
                               
 
				 //let's try this with shapes instead.....
                                for (unsigned int i = 0; i < mGame->mShapeVector.size(); i++)
                                {
                                        if (mGame->mShapeVector.at(i)->mClient != NULL)
                                        {
                                               	if (mGame->mShapeVector.at(i)->mClient->mClientID == clientID) 
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
