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

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

//postgresql
#include <stdio.h>
#include <postgresql/libpq-fe.h>


#include "../quiz/quiz.h"
//server side client constructor, many instances will be made, one for each client connected.
Client::Client(Server* server, struct sockaddr *address, int clientID)
{
	//logged in
	mLoggedIn = false;

	//client id for php but everyone uses one...
	mClientID = clientID;
	
	//db
	db_id = 0;
	db_school_id = 0;

	//game
	mGame = NULL;
	
	//shape
	mShape = NULL;

	//server
	mServer = server;

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

void Client::setSocketAddress(struct sockaddr *address)
{
	memcpy(&mSocketAddress, address, sizeof(struct sockaddr)); 
}

void Client::processUpdate()
{
	checkForTimeout();	
	if (mGame)
	{
	}
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
	mLoggedIn = false;

        mMessage.Init(mMessage.outgoingData, sizeof(mMessage.outgoingData));
        mMessage.WriteByte(mServer->mMessageLoggedOut); // add type
	if (mClientID > 0)
	{
        	mMessage.WriteByte(mClientID); //client id for browsers
	}	
	mServer->mNetwork->sendPacketTo(this,&mMessage);
}

void Client::checkLogin(Message* mes)
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
        
	Client* client;
	//check against db
        if (getPasswordMatch(mStringUsername,mStringPassword))
     	{ 
		for (unsigned int i = 0; i < mServer->mClientVector.size(); i++)
		{
			if (mServer->mClientVector.at(i)->db_id == db_id)
			{
				if (mServer->mClientVector.at(i) == this)
				{
					login();
				}
			}	
		}
		for (unsigned int i = 0; i < mServer->mClientVector.size(); i++)
		{
			if (mServer->mClientVector.at(i)->db_id == db_id)
			{
				//logout old 
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
        	logout();
        }
}

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
		logout();
		LogString("logging out.. you should fire up ai for:%d",mClientID);
        }
}

