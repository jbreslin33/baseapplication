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
#include "../game/gameMath.h"

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
	mNetwork = new Network(localIP, mPort);

	//this will need updating whenever a new school is added to db...
	getSchools();	

	//get questions
	getQuestions();

	//create games
	mGameVector.push_back(new Game(this,1));
	mGameVector.push_back(new Game(this,2));
}

Server::~Server()
{
	mClientVector.empty();
	mNetwork->closeSocket(mNetwork->mSocket);
}



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

void Server::addClient(Client* client)
{
	mClientVector.push_back(client);
}

void Server::addGame(Game* game)
{
	mGameVector.push_back(game);
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
		Client* client = new Client(this, address, 0);
	}

	else if (type == mMessageConnectBrowser)
	{
		int clientID = mes->ReadByte();
 		Client* client = new Client(this, address, clientID);
	}

	else if (type == mMessageConnectNode)
	{
		int clientID = mes->ReadByte();
 		Client* client = new Client(this, address, -1);
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
						client->joinGame(mGameVector.at(g)); //now call everything else inside client...
						LogString("joinGame:%d",g);
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
						client->joinGame(mGameVector.at(g)); //now call everything else inside client...
						LogString("joinGame:%d",g);
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
	}

	else if (type == mMessageLoginBrowser)
	{
                int clientID = mes->ReadByte();
		for (int i = 0; i < mClientVector.size(); i++)
		{
			if (mClientVector.at(i)->mClientID == clientID)
			{
                                //set client to pointer
                                client = mClientVector.at(i);
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
				client->leaveGame();
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
				client->leaveGame();
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

	else if (type == mMessageDisconnect)
	{
	
 		// Find the correct client by comparing addresses
                for (unsigned int i = 0; i < mClientVector.size(); i++)
                {
                        if( memcmp(mClientVector.at(i)->GetSocketAddress(), address, sizeof(address)) == 0)
                        {
				//delete client
                                client = mClientVector.at(i);
				delete client;

 				//erase client from vector
                        	mClientVector.erase(mClientVector.begin()+i);
				LogString("c++ client deleted");
			}
		}

	}

	else if (type == mMessageDisconnectBrowser)
	{
 		int clientID = mes->ReadByte();

                for (unsigned int i = 0; i < mClientVector.size(); i++)
                {
                        if (mClientVector.at(i)->mClientID == clientID)
                        {
				LogString("Browser client deleted, you should delete shape too...");
                                client = mClientVector.at(i);
				delete client;
			}
		}
	}
}

int Server::checkForTimeout()
{
	int currentTime = mNetwork->getCurrentSystemTime();

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

void Server::getSchools()
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
        for (row=0; row<rec_count; row++)
        {
		const char* c = PQgetvalue(res, row, 1);  
		std::string school(c);
		
		mSchoolVector.push_back(school);
        }

        PQclear(res);

        PQfinish(conn);
}

void Server::getQuestions()
{
        PGconn          *conn;
        PGresult        *res;
        int             rec_count;
        int             row;
        int             col;
        conn = PQconnectdb("dbname=abcandyou host=localhost user=postgres password=mibesfat");
        res = PQexec(conn,
       "select * from questions ORDER BY id");
        if (PQresultStatus(res) != PGRES_TUPLES_OK)
        {
                puts("We did not get any data!");
                //exit(0);
        }
        rec_count = PQntuples(res);
        printf("We received %d records.\n", rec_count);
        for (row=0; row<rec_count; row++)
        {
                const char* a = PQgetvalue(res, row, 0);
                std::string aString(a);
                mQuestionIDVector.push_back(aString);

                const char* b = PQgetvalue(res, row, 1);
                std::string bString(b);
                mQuestionsVector.push_back(bString);

                const char* c = PQgetvalue(res, row, 2);
                std::string cString(c);
                mAnswersVector.push_back(cString);

                const char* d = PQgetvalue(res, row, 3);
                std::string dString(d);
                mLevelsVector.push_back(dString);
        }

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


