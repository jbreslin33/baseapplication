//parent
#include "client.h"

//log
#include "../tdreamsock/dreamSockLog.h"

//message
#include "../message/message.h"

//network
#include "../network/network.h"

//server
#include "../server/server.h"

//game
#include "../game/game.h"

//shape
#include "../shape/shape.h"

//abilitys
#include "../ability/rotation/rotation.h"
#include "../ability/move/move.h"

//math
#include "../../math/vector3D.h"

#ifdef WIN32
//
#else
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#endif

//postgresql
#include <stdio.h>
#include <postgresql/libpq-fe.h>


#include "../quiz/quiz.h"
//server side client constructor, many instances will be made, one for each client connected.
Client::Client(Server* server, struct sockaddr *address, int clientID)
{
        //keys
        mKeyUp = 1;
        mKeyDown = 2;
        mKeyLeft = 4;
        mKeyRight = 8;
        mKeyCounterClockwise = 16;
        mKeyClockwise = 32;

	//logged in
	mLoggedIn = false;

	//client id for php but everyone uses one...
	mClientID = clientID;
	
	//db
	db_id = 0;
	db_school_id = 0;

	//game--there should be a vector as well. and a mGame to show what the user is playing right now if any 
	mGame = NULL;
	
	//shape
	mShape = NULL;

	//server
	mServer = server;

	//key
	mKey = 0;
	mKeyLast = 0;
	
	mLastMessageTime = mServer->mNetwork->getCurrentSystemTime();

	if (!address)
	{
		mConnectionState  = DREAMSOCK_DISCONNECTED;
	}
	else
	{
		setSocketAddress(address);
		mConnectionState  = DREAMSOCK_CONNECTING;
	}

	if (mClientID >= 0)
	{
       		sendConnected();
	}
	else
	{
		//your the node for web sockets or a dummy ai client using node address temporarily
	}
}

Client::~Client()
{
	//this will check if there is an mShape

	if (mGame)
	{
		mGame->leave(this);
	}

	for (unsigned int i = 0; i < mServer->mClientVector.size(); i++)
        {
                if (mServer->mClientVector.at(i) == this)
		{
 			mServer->mClientVector.erase(mServer->mClientVector.begin()+i);
		}
	}
}

//game
Game* Client::getGame()
{
	return mGame;
}

void Client::addGame(Game* game)
{
	mGameVector.push_back(game);
} 

void Client::setGame(int gameID)
{
	
 	for (int i = 0; i < mGameVector.size(); i++)
        {
        	if (mGameVector.at(i)->mID == gameID)
               	{
               		mGame = mGameVector.at(i);
			mGame->sendShapes(this);
			LogString("Client::ControlGame:%d",gameID);
                }
	}	
}

//shape
void Client::setShape(Shape* shape)
{
        mShape = shape;
}


void Client::setSocketAddress(struct sockaddr *address)
{
	memcpy(&mSocketAddress, address, sizeof(struct sockaddr)); 
}

void Client::processUpdate()
{
}

void Client::remove()
{
	for (unsigned int i = 0; i < mServer->mClientVector.size(); i++)
	{
		if (mServer->mClientVector.at(i) == this)
		{
			//mServer->mClientVector.erase(mServer->mClientVector.begin()+i);
			///delete this;
		}
	}
}

//connected
void Client::sendConnected()
{
        mMessage.Init(mMessage.outgoingData, sizeof(mMessage.outgoingData));
        mMessage.WriteByte(mServer->mMessageConnected); // add type
	if (mClientID > 0)
	{
        	mMessage.WriteByte(mClientID); // add mClientID for browsers 
	}
	mServer->mNetwork->sendPacketTo(this,&mMessage);
}

//login
//i should send db_id back as well.....because once a client connects we are not going to delete it..... we will just manage it best we can from here on server....
//which means when you login from a new address we will send a notification to old address as a courtesy....
void Client::login()
{
	LogString("sending login to clientID:%d",mClientID);

	//set last messageTime
	mLastMessageTime = mServer->mNetwork->getCurrentSystemTime();

	mLoggedIn = true;

        mMessage.Init(mMessage.outgoingData, sizeof(mMessage.outgoingData));
        mMessage.WriteByte(mServer->mMessageLoggedIn); // add type
	if (mClientID > 0)
	{
        	mMessage.WriteByte(mClientID); //client id for browsers
	}	
	mServer->mNetwork->sendPacketTo(this,&mMessage);
}

void Client::logout()
{
	LogString("sending logout to clientID:%d",mClientID);
	mLoggedIn = false;

        mMessage.Init(mMessage.outgoingData, sizeof(mMessage.outgoingData));
        mMessage.WriteByte(mServer->mMessageLoggedOut); // add type
	if (mClientID > 0)
	{
        	mMessage.WriteByte(mClientID); //client id for browsers
	}	
	mServer->mNetwork->sendPacketTo(this,&mMessage);
}

void Client::readLoginMessage(Message* mes)
{
	//clear username and password strings
        mStringUsername.clear();
        mStringPassword.clear();

        int sizeOfUsername = mes->ReadByte();
        int sizeOfPassword = mes->ReadByte();

        //loop thru and set mStringUsername from client
        for (int i = 0; i < sizeOfUsername; i++)
        {
                if (mClientID > 0)
                {
                        char c = mes->ReadByte();
                        mStringUsername.append(1,c);
                }
                else
                {
                        int numeric = mes->ReadByte();
                        char ascii = (char)numeric;
                        mStringUsername.append(1,ascii);
                }
        }

        //loop thru and set mStringPassword from client
        for (int i = 0; i < sizeOfPassword; i++)
        {
                if (mClientID > 0)
                {
                        char c = mes->ReadByte();
                        mStringPassword.append(1,c);
                }
                else
                {
                        int numeric = mes->ReadByte();
                        char ascii = (char)numeric;
                        mStringPassword.append(1,ascii);
                }
        }
}

bool Client::checkLogin(Message* mes)
{
	readLoginMessage(mes);

	//let's find what permanent client you are trying to login to	
	for (unsigned int i = 0; i < mServer->mClientVector.size(); i++)
	{
		//do you match the username/password?
		if (mStringUsername.compare(mServer->mClientVector.at(i)->db_username) == 0 && mStringPassword.compare(mServer->mClientVector.at(i)->db_password) == 0)
		{
			LogString("match!!!:%d",mClientID);			
			//we could have the same client log back in with same up	
			if (this == mServer->mClientVector.at(i))
			{
				login();	
			}
			else //we have a diff client but a pass match...
			{
				//for (unsigned int b = 0; b < mServer->mClientVector.size(); b++)
				//{
				//	if (this == mClientVector	

				//logout client who is logged in under this uname
				//mServer->mClientVector.at(i)->logout();
				//let's disconnect this client because it used to control someone
				//logout();
				mConnectionState = DREAMSOCK_DISCONNECTED; 

                                //swap
                                mServer->mClientVector.at(i)->setSocketAddress(&mSocketAddress);
                                mServer->mClientVector.at(i)->mConnectionState = DREAMSOCK_CONNECTED;
                                mServer->mClientVector.at(i)->mClientID = mClientID;
                                mServer->mClientVector.at(i)->login();
	//			}
			}
			
		}
		else
		{
		}
	}
}

/*
bool Client::checkLogin(Message* mes)
{
	readLoginMessage(mes);

        if (getPasswordMatch(mStringUsername,mStringPassword))
     	{
		Client* loginClient = NULL; 
		for (unsigned int i = 0; i < mServer->mClientVector.size(); i++)
		{
			if (mServer->mClientVector.at(i)->db_id == db_id)
			{
				if (mServer->mClientVector.at(i) == this)
				{
					loginClient = mServer->mClientVector.at(i);
					login();
				}
			}	
		}
		for (unsigned int i = 0; i < mServer->mClientVector.size(); i++)
		{
			if (mServer->mClientVector.at(i)->db_id == db_id)
			{
				//logout old 
				if (loginClient == mServer->mClientVector.at(i))
				{
					LogString("returning");
					return true;
				}
				LogString("should not get to this logout!!!");
				mServer->mClientVector.at(i)->logout();

				//swap
				mServer->mClientVector.at(i)->setSocketAddress(&mSocketAddress);
				mServer->mClientVector.at(i)->mConnectionState = DREAMSOCK_CONNECTED;
				mServer->mClientVector.at(i)->mClientID = mClientID;
				mServer->mClientVector.at(i)->login();
			}	
		}
        }
        else
        {
		LogString("else logout");	
        	logout();
        }
}
*/
bool Client::getPasswordMatch(std::string username,std::string password)
{
        PGconn          *conn;
        PGresult        *res;
        int             rec_count;
        int             row;
        int             col;
        bool match = false;
        std::string query = "select id, username, password from users where username = '";
        std::string a = "' ";
        std::string b = "and password = '";
        std::string c = "'";

        query.append(username);
        query.append(a);
        query.append(b);
        query.append(password);
        query.append(c);

        const char * q = query.c_str();

        conn = PQconnectdb("dbname=abcandyou host=localhost user=postgres password=mibesfat");

        res = PQexec(conn,q);
        if (PQresultStatus(res) != PGRES_TUPLES_OK)
        {
                puts("We did not get any data!");
                //exit(0);
        }
        rec_count = PQntuples(res);
        if (rec_count > 0)
        {
		const char* value = PQgetvalue(res, row, 0);
		stringstream strValue;
		strValue << value;
		unsigned int intValue;
		strValue >> intValue;
		db_id = intValue;
	
                match = true;
        }

        PQclear(res);

        PQfinish(conn);

        return match;
}

void Client::checkForTimeout()
{
        // Don't timeout when connecting or if logged out...
        if(mLoggedIn == false || mConnectionState == DREAMSOCK_CONNECTING)
        {
        	return;
        }

        int currentTime = mServer->mNetwork->getCurrentSystemTime();

        // Check if the client has been silent for 30 seconds if so log him out and start ai up...
        if(currentTime - mLastMessageTime > 30000)
        {
		LogString("timeout logout");
		logout();
		LogString("logging out.. you should fire up ai for:%d",mClientID);
        }
}

