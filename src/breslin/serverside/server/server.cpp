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

//math
#include "../../math/vector3D.h"

//postgresql
#include <stdio.h>
#include <postgresql/libpq-fe.h>

Server::Server(Ogre::Root* root, const char *localIP, int serverPort)
{
	//ogre root
	mRoot = root;

        //sequence
        mOutgoingSequence = 1;

	//time
	mTickLength = 32;
 	mFrameTime  = 0;
        mGameTime   = 0;
        mFrameTimeLast  = 0;

	mLocalIP = localIP;
	
	// Store the server IP and port for later use
	mPort = serverPort;

	// Create network
	mNetwork = new Network(this,localIP, mPort);
}

Server::~Server()
{
	mClientVector.empty();
	mClientVectorTemp.empty();
	mNetwork->closeSocket(mNetwork->mSocket);
}


/*******************************************************
		GAMES	
********************************************************/

void Server::createGames()
{
	//create games for now just create standard no frills game of you get to collide with stuff in multiplayer....
	mGameVector.push_back(new Game(this,1));
}

/*******************************************************
		UPDATES	
********************************************************/
void Server::processUpdate(int msec)
{
 	mFrameTime += msec;
        mGameTime += msec;

	readPackets();

	//update clients
  	for (unsigned int i = 0; i < mClientVector.size(); i++)
	{
		mClientVector.at(i)->processUpdate();
	}

	//update games
  	for (unsigned int i = 0; i < mGameVector.size(); i++)
	{
		mGameVector.at(i)->processUpdate();
	}

        // Wait full 32 ms before allowing to send
        if(mFrameTime < mTickLength)
        {
                return;
        }

        //send positions and exact frame time the calcs where done on which is mFrameTime
 	for (unsigned int i = 0; i < mGameVector.size(); i++)
        {
		sendCommand(mGameVector.at(i));
	}

        mFrameTimeLast = mFrameTime;
        mFrameTime = 0;
}

/*******************************************************
		CLIENTS	
********************************************************/
void Server::createClients()
{
        PGconn          *conn;
        PGresult        *res;
        int             rec_count;
        int             row;
        int             col;
        conn = PQconnectdb("dbname=abcandyou host=localhost user=postgres password=mibesfat");
        res = PQexec(conn,"select * from users ORDER BY id");
        if (PQresultStatus(res) != PGRES_TUPLES_OK)
        {
                puts("We did not get any data!");
        }
        rec_count = PQntuples(res);
        printf("We received %d records from user table.\n", rec_count);
        for (row=0; row<rec_count; row++)
        {
                //client
                Client* client = new Client(this, NULL, -2);
		addClient(client,true);	

                //id
                const char* a = PQgetvalue(res, row, 0);
                stringstream a_str;
                a_str << a;
                unsigned int a_int;
                a_str >> a_int;
                client->db_id = a_int;

                //username
                const char* b = PQgetvalue(res, row, 1);
                client->db_username.assign(b);

                //password
                const char* c = PQgetvalue(res, row, 2);
                client->db_password.assign(c);

                //first_name
                const char* d = PQgetvalue(res, row, 3);
                client->db_first_name.assign(d);

                //last_name
                const char* e = PQgetvalue(res, row, 7);
                client->db_last_name.assign(e);

   		//school_id
                const char* f = PQgetvalue(res, row, 8);
                stringstream f_str;
                f_str << f;
                unsigned int f_int;
                f_str >> f_int;
                client->db_school_id = f_int;
        }
        PQclear(res);
        PQfinish(conn);
}

void Server::addClient(Client* client, bool permanent)
{
	if (permanent)
	{
		mClientVector.push_back(client);
	}
	else
	{
		mClientVectorTemp.push_back(client);
	}
}





/*******************************************************
		PACKETS
********************************************************/
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

	ret = mNetwork->getPacket(mNetwork->mSocket, mes.data, from);

	if(ret <= 0)
	{	
		return 0;
	}

	mes.SetSize(ret);

	// Parse system messages
	parsePacket(&mes, from);

	return ret;
}

void Server::parsePacket(Message *mes, struct sockaddr *address)
{
	Client* client;
	mes->BeginReading();

	int type = mes->ReadByte();
	
	/***CONNECT********/
	//this should just create a client then client should do what need be done.
	if (type == mMessageConnect)
	{
		LogString("client %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%");
		Client* client = new Client(this, address, 0);
		addClient(client,false);
	}

	else if (type == mMessageConnectBrowser)
	{
		int clientID = mes->ReadByte();
 		Client* client = new Client(this, address, clientID);
		addClient(client,false);
	}

	else if (type == mMessageConnectNode)
	{
		LogString("Connect node.... %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%");
		int clientID = mes->ReadByte();
 		Client* client = new Client(this, address, -1);
		addClient(client,true);
	}	

	/***JOIN GAME********/
	/* can i just send more information here for different games?                      */
	else if (type == mMessageJoinGame)
	{
		int gameID = mes->ReadByte();

		for (unsigned int i = 0; i < mClientVector.size(); i++)
		{
			if( memcmp(mClientVector.at(i)->GetSocketAddress(), address, sizeof(address)) == 0)
			{
				//get client
				client = mClientVector.at(i);
			
				//call clients join game function
				for (int g = 0; g < mGameVector.size(); g++)
				{ 
					if (mGameVector.at(g)->mID == gameID)
					{
						mGameVector.at(g)->join(client); 
						LogString("join");
					}
				}
			}
		}
	}
	
	else if (type == mMessageJoinGameBrowser)
	{
                int clientID = mes->ReadByte();
		int gameID   = mes->ReadByte();

		for (int i = 0; i < mClientVector.size(); i++)
		{
			if (mClientVector.at(i)->mClientID == clientID)
			{
 				//get client
                                client = mClientVector.at(i);

				//call clients join game function
				for (int g = 0; g < mGameVector.size(); g++)
				{ 
					if (mGameVector.at(g)->mID == gameID)
					{
						mGameVector.at(g)->join(client); 
					}
				}
                                
			}
                }
	}

	/******* LOGIN **********/
	else if (type == mMessageLogin)
	{
 		//get client	
		for (unsigned int i = 0; i < mClientVector.size(); i++)
                {
                        if( memcmp(mClientVector.at(i)->GetSocketAddress(), address, sizeof(address)) == 0)
                        {
				//set client to pointer
                                client = mClientVector.at(i);
				client->checkLogin(mes);
			}
                }

		for (unsigned int i = 0; i < mClientVectorTemp.size(); i++)
                {
                        if( memcmp(mClientVectorTemp.at(i)->GetSocketAddress(), address, sizeof(address)) == 0)
                        {
				//set client to pointer
                                client = mClientVectorTemp.at(i);
				client->checkLogin(mes);
			}
		}
	}

	else if (type == mMessageLoginBrowser)
	{
                int clientID = mes->ReadByte();
		LogString("login attempt for clientID:%d",clientID);
		for (int i = 0; i < mClientVector.size(); i++)
		{
			if (mClientVector.at(i)->mClientID == clientID)
			{
                                //set client to pointer
                                client = mClientVector.at(i);
				client->checkLogin(mes);
			}
		}	
		for (int i = 0; i < mClientVectorTemp.size(); i++)
		{
			if (mClientVectorTemp.at(i)->mClientID == clientID)
			{
                                //set client to pointer
                                client = mClientVectorTemp.at(i);
				client->checkLogin(mes);
			}
		}
	}

	/***LOG OUT********/
	else if (type == mMessageLogout)
	{
 		//get client 
                for (unsigned int i = 0; i < mClientVector.size(); i++)
                {
                        if( memcmp(mClientVector.at(i)->GetSocketAddress(), address, sizeof(address)) == 0)
                        {
                                //set client to pointer
                                client = mClientVector.at(i);
				client->logout();
			}
		}
	}

        else if (type == mMessageLogoutBrowser)
        {
                int clientID = mes->ReadByte();
                for (int i = 0; i < mClientVector.size(); i++)
                {
                        if (mClientVector.at(i)->mClientID == clientID)
                        {
                                //set client to pointer
                                client = mClientVector.at(i);
				client->logout();
			}
		}
	}
                           	
	/***QUIT GAME********/
	else if (type == mMessageQuitGame)
	{
		// Find the correct client by comparing addresses
		for (unsigned int i = 0; i < mClientVector.size(); i++)
		{
			if( memcmp(mClientVector.at(i)->GetSocketAddress(), address, sizeof(address)) == 0)
			{
				client = mClientVector.at(i);
				client->mGame->leave(client);
			}
		}
	}

	else if (type == mMessageQuitGameBrowser)
	{
                int clientID = mes->ReadByte();
		for (int i = 0; i < mClientVector.size(); i++)
		{
			if (mClientVector.at(i)->mClientID == clientID)
			{
				client = mClientVector.at(i);
				client->mGame->leave(client);
			}
		}
	}
	
	else if (type == mMessageFrame)
	{
		// Find the correct client by comparing addresses
		for (unsigned int i = 0; i < mClientVector.size(); i++)
		{
			if( memcmp(mClientVector.at(i)->GetSocketAddress(), address, sizeof(address)) == 0)
			{
				client = mClientVector.at(i);
				client->mLastMessageTime = mNetwork->getCurrentSystemTime();
                                client->mGame->readDeltaMoveCommand(mes,client);
				
				// Wait for one message before setting state to connected
                                if(client->mConnectionState == DREAMSOCK_CONNECTING)
                                {
                                        client->mConnectionState = DREAMSOCK_CONNECTED;
                                }
			}
		}
	}
	
	else if (type == mMessageFrameBrowser)
	{
		int clientID = mes->ReadByte();
		
		for (unsigned int i = 0; i < mClientVector.size(); i++)
		{
			if (mClientVector.at(i)->mClientID == clientID)
			{
				client = mClientVector.at(i);
				client->mLastMessageTime = mNetwork->getCurrentSystemTime();
                                client->mGame->readDeltaMoveCommand(mes,client);
  				// Wait for one message before setting state to connected
        			if(client->mConnectionState == DREAMSOCK_CONNECTING)
        			{
                			client->mConnectionState = DREAMSOCK_CONNECTED;
        			}
			}
		}
	} 
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

		mNetwork->sendPacketTo(mClientVector.at(i),&mMessage);
			
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
			//you could do something here, what i have no idea yet..	
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

void Server::sendCommand(Game* game)
{
        // Fill messages..for all clients
        //standard initialize of mMessage for client in this case
        mMessage.Init(mMessage.outgoingData,
                sizeof(mMessage.outgoingData));

        //start filling said mMessage that belongs to client
        mMessage.WriteByte(mMessageFrame);                    // type

        mMessage.WriteShort(mOutgoingSequence);

        //frame time
        mMessage.WriteByte(mFrameTime);

        //this is where you need to actually loop thru the shapes not the clients but put write to client mMessage
        for (unsigned int j = 0; j < game->mShapeVector.size(); j++)
        {                         //the client to send to's message        //the shape command it's about
                game->mShapeVector.at(j)->addToMoveMessage(&mMessage);
        }

        sendPackets();

        // Store the sent command in
        for (unsigned int i = 0; i < game->mShapeVector.size(); i++)
        {
                storeCommands(game->mShapeVector.at(i));
        }
}

void Server::storeCommands(Shape* shape)
{
        shape->mKeyLast = shape->mKey;

        shape->mPositionLast->convertFromVector3(shape->mSceneNode->getPosition());

        shape->mRotationLast->copyValuesFrom(shape->mRotation);
}


