//parent
#include "client.h"

//log
#include "../tdreamsock/dreamSockLog.h"

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


//server side client constructor, many instances will be made, one for each client connected.
Client::Client(Server* server, struct sockaddr *address)
{
	//loggedIn
	mLoggedIn = false;

	//set client id to 0 as this will identify it as a c++ or java client
	mClientID = 0;	

	//server
	mServer = server;

	mLastMessageTime  = 0;
	mConnectionState  = DREAMSOCK_CONNECTING;

	SetSocketAddress(address);

	//register this client with server
	mServer->addClient(this);
       	
	sendConnected();
        sendSchools();
}

//server side client constructor, many instances will be made, one for each client connected.
Client::Client(Server* server, struct sockaddr *address, int clientID)
{
	mLoggedIn = false;

	//set client id as this is going to be a browser client
	//-1 = browser client to udp_server.js, no shape 
	//0 = c++ client, obviously a shape 
	//1 or greater than client represents a browser client and should have a shape
	mClientID = clientID;

	//server
	mServer = server;

	mLastMessageTime  = 0;
	mConnectionState  = DREAMSOCK_CONNECTING;

	SetSocketAddress(address);

	//register this client with server
	mServer->addClient(this);

	if (mClientID > 0)
	{
       		sendConnected();
        	sendSchools();
	}
}

Client::~Client()
{
	//this will check if there is an mShape
	leaveGame();

	for (unsigned int i = 0; i < mServer->mClientVector.size(); i++)
        {
                if (mServer->mClientVector.at(i) == this)
		{
 			mServer->mClientVector.erase(mServer->mClientVector.begin()+i);
		}
	}
}

//it's only fair to send a remove shape to everybody as well.....

void Client::joinGame()
{
	//let this client know about all shapes
	if (mClientID > 0)
	{
        	sendAllShapesBrowser();
	}
	else
	{
        	sendAllShapes();
	}

	//create the shape for this client -- the avatar
	mShape = new Shape(mServer->mGame->getOpenIndex(),mServer->mGame,this,mServer->mGame->getOpenPoint(),new Vector3D(),new Vector3D(),mServer->mGame->mRoot,true,true,.66f * 30.5,1,false); 
}

void Client::leaveGame()
{
	//you gotta delete the shape here...and tell everyone about it. i would tell them in shape class
	if (mShape)
	{
        	mServer->mMessage.Init(mServer->mMessage.outgoingData, sizeof(mServer->mMessage.outgoingData));
        	mServer->mMessage.WriteByte(mServer->mMessageLeaveGame); // add type
		//tell human client that it has left game 
		if (mClientID > 0)
		{	
        		mServer->mMessage.WriteByte(mClientID); //client id for browsers
		}
		SendPacket(&mServer->mMessage);

		mShape->remove();
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

void Client::sendSchools()
{
	//loop thru each char... 
	for (unsigned int i = 0; i < mServer->mSchoolVector.size(); i++)
	{
        	mServer->mMessage.Init(mServer->mMessage.outgoingData, sizeof(mServer->mMessage.outgoingData));
        	mServer->mMessage.WriteByte(mServer->mMessageAddSchool); // add type
		if (mClientID > 0)
		{
        		mServer->mMessage.WriteByte(mClientID); // add mClientID for browsers 
		}
		int length = mServer->mSchoolVector.at(i).length();  // get length of string containing school 
		mServer->mMessage.WriteByte(length); //send length 

		//loop thru length and write it 
		for (int b=0; b < length; b++)
		{
			mServer->mMessage.WriteByte(mServer->mSchoolVector.at(i).at(b));		
		}
		
		//send it
		SendPacket(&mServer->mMessage);
	}
}

void Client::sendAllShapes()
{
	for (unsigned int i = 0; i < mServer->mGame->mShapeVector.size(); i++)
	{
		if (mShape != mServer->mGame->mShapeVector.at(i))
		{
			//write it
			mServer->mGame->mShapeVector.at(i)->writeAdd(this);
		
			//send it
			SendPacket(&mServer->mMessage);
		}
	}
}

void Client::sendAllShapesBrowser()
{
	for (unsigned int i = 0; i < mServer->mGame->mShapeVector.size(); i++)
	{
		if (mShape != mServer->mGame->mShapeVector.at(i))
		{
			//write it
			mServer->mGame->mShapeVector.at(i)->writeAddBrowser(this);
		
			//send it
			SendPacket(&mServer->mMessage);
		}
	}
}

void Client::sendQuestion()
{
	//generate question based on level etc
	
	
	//send it
	//SendPacket(...
//	you could actually just SendPacket in writeQuestion and writeQuestionBrowser because we are not looping
//but we will not because it confuses this.
}

//connected
void Client::sendConnected()
{
        mServer->mMessage.Init(mServer->mMessage.outgoingData, sizeof(mServer->mMessage.outgoingData));
        mServer->mMessage.WriteByte(mServer->mMessageConnected); // add type
	if (mClientID > 0)
	{
        	mServer->mMessage.WriteByte(mClientID); // add mClientID for browsers 
	}
	SendPacket(&mServer->mMessage);
}

//login
void Client::login()
{
	mLoggedIn = true;

        mServer->mMessage.Init(mServer->mMessage.outgoingData, sizeof(mServer->mMessage.outgoingData));
        mServer->mMessage.WriteByte(mServer->mMessageLoggedIn); // add type
	if (mClientID > 0)
	{
        	mServer->mMessage.WriteByte(mClientID); //client id for browsers
	}	
	SendPacket(&mServer->mMessage);
}

void Client::logout()
{
	mLoggedIn = false;

        mServer->mMessage.Init(mServer->mMessage.outgoingData, sizeof(mServer->mMessage.outgoingData));
        mServer->mMessage.WriteByte(mServer->mMessageLoggedOut); // add type
	if (mClientID > 0)
	{
        	mServer->mMessage.WriteByte(mClientID); //client id for browsers
	}	
	SendPacket(&mServer->mMessage);
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

void Client::writeQuestion()
{

}

void Client::writeQuestionBrowser()
{
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
		mServer->mGame->mOutgoingSequence++;
	}
}


