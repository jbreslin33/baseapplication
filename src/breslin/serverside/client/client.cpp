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
}

Client::~Client()
{
	mServer->mNetwork->dreamSock_CloseSocket(mServer->mNetwork->mSocket);
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
	mShape = new Shape(mServer->mGame->getOpenIndex(),mServer->mGame,this,new Vector3D(),new Vector3D(),new Vector3D(),mServer->mGame->mRoot,true,true,.66f,1,false); 
}

void Client::leaveGame()
{

	//you gotta delete the shape here...and tell everyone about it. i would tell them in shape class
	if (mShape)
	{
		mShape->remove();
	}	

	//tell human client that it has left game 

	if (mClientID > 0)
	{	
        	mServer->mMessage.Init(mServer->mMessage.outgoingData, sizeof(mServer->mMessage.outgoingData));
        	mServer->mMessage.WriteByte(mServer->mMessageLeaveGame); // add type
        	mServer->mMessage.WriteByte(mClientID); //client id for browsers
	}
	else
	{
        	mServer->mMessage.Init(mServer->mMessage.outgoingData, sizeof(mServer->mMessage.outgoingData));
        	mServer->mMessage.WriteByte(mServer->mMessageLeaveGame); // add type
	}

	SendPacket(&mServer->mMessage);
}

void Client::remove()
{
	for (unsigned int i = 0; i < mServer->mClientVector.size(); i++)
	{
		if (mServer->mClientVector.at(i) == this)
		{
			mServer->mClientVector.erase(mServer->mClientVector.begin()+i);
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

void Client::sendLoggedIn()
{
        mServer->mMessage.Init(mServer->mMessage.outgoingData, sizeof(mServer->mMessage.outgoingData));
        mServer->mMessage.WriteByte(mServer->mMessageLoggedIn); // add type
	SendPacket(&mServer->mMessage);
}

void Client::sendLoggedInBrowser()
{
	LogString("sendLoggedInBrowser dude");
        mServer->mMessage.Init(mServer->mMessage.outgoingData, sizeof(mServer->mMessage.outgoingData));
        mServer->mMessage.WriteByte(mServer->mMessageLoggedIn); // add type
        mServer->mMessage.WriteByte(mClientID); //client id for browsers
	SendPacket(&mServer->mMessage);
}

void Client::sendLoggedOut()
{
        mServer->mMessage.Init(mServer->mMessage.outgoingData, sizeof(mServer->mMessage.outgoingData));
        mServer->mMessage.WriteByte(mServer->mMessageLoggedOut); // add type
	SendPacket(&mServer->mMessage);
}

void Client::sendLoggedOutBrowser()
{
        mServer->mMessage.Init(mServer->mMessage.outgoingData, sizeof(mServer->mMessage.outgoingData));
        mServer->mMessage.WriteByte(mServer->mMessageLoggedOut); // add type
        mServer->mMessage.WriteByte(mClientID); //client id for browsers
        SendPacket(&mServer->mMessage);
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


