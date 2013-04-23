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
	//quiz
	mQuiz = NULL;

	mLoggedIn = false;

	//set client id as this is going to be a browser client
	//-1 = browser client to udp_server.js, no shape 
	//0 = c++ client, obviously a shape 
	//1 or greater than client represents a browser client and should have a shape
	mClientID = clientID;

	//game
	mGame = NULL;

	//server
	mServer = server;

	mLastMessageTime  = 0;
	mConnectionState  = DREAMSOCK_CONNECTING;

	SetSocketAddress(address);

	//register this client with server
	mServer->addClient(this);


	if (mClientID >= 0)
	{
       		sendConnected();
        	sendSchools();
	}
	else
	{
		//your the node for web sockets
	}
}

Client::~Client()
{
	//this will check if there is an mShape
	mGame->leave(this);

	for (unsigned int i = 0; i < mServer->mClientVector.size(); i++)
        {
                if (mServer->mClientVector.at(i) == this)
		{
 			mServer->mClientVector.erase(mServer->mClientVector.begin()+i);
		}
	}
}

void Client::processUpdate()
{
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

//you need to send all schools at once and all questions..
void Client::sendSchools()
{
	//loop thru each char... 
	for (unsigned int i = 0; i < mServer->mSchoolVector.size(); i++)
	{
        	mMessage.Init(mMessage.outgoingData, sizeof(mMessage.outgoingData));
        	mMessage.WriteByte(mServer->mMessageAddSchool); // add type
		if (mClientID > 0)
		{
        		mMessage.WriteByte(mClientID); // add mClientID for browsers 
		}
		int length = mServer->mSchoolVector.at(i).length();  // get length of string containing school 
		mMessage.WriteByte(length); //send length 

		//loop thru length and write it 
		for (int b=0; b < length; b++)
		{
			mMessage.WriteByte(mServer->mSchoolVector.at(i).at(b));		
		}
		
		//send it
	//	SendPacket(&mMessage);
		mServer->mNetwork->sendPacketTo(this,&mMessage,&mMyaddress);
	}
}

void Client::sendQuestion(int id)
{
        //loop thru each char...
	mMessage.Init(mMessage.outgoingData, sizeof(mMessage.outgoingData));
       	mMessage.WriteByte(mServer->mMessageAddQuestion); // add type
       	if (mClientID > 0)
       	{
       	         mMessage.WriteByte(mClientID); // add mClientID for browsers
       	}
       	int length = mServer->mSchoolVector.at(id).length();  // get length of string containing school
       	mMessage.WriteByte(length); //send length

       	//loop thru length and write it
       	for (int i=0; i < length; i++)
       	{
       		mMessage.WriteByte(mServer->mQuestionsVector.at(id).at(i));             
       	}

       	//send it
	mServer->mNetwork->sendPacketTo(this,&mMessage,&mMyaddress);
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
	mServer->mNetwork->sendPacketTo(this,&mMessage,&mMyaddress);
}

//login
void Client::login()
{
	mLoggedIn = true;

        mMessage.Init(mMessage.outgoingData, sizeof(mMessage.outgoingData));
        mMessage.WriteByte(mServer->mMessageLoggedIn); // add type
	if (mClientID > 0)
	{
        	mMessage.WriteByte(mClientID); //client id for browsers
	}	
	mServer->mNetwork->sendPacketTo(this,&mMessage,&mMyaddress);
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
	mServer->mNetwork->sendPacketTo(this,&mMessage,&mMyaddress);
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
        
	//check against db
        if (getPasswordMatch(mStringUsername,mStringPassword))
     	{ 
        	login();
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
        std::string query = "select username,password from users where username = '";
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
                match = true;
        }

        PQclear(res);

        PQfinish(conn);

        return match;
}

