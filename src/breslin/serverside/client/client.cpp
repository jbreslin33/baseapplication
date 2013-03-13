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
	//set client id to 0 as this will identify it as a c++ or java client
	mClientID = 0;	

	//server
	mServer = server;

	mLastMessageTime  = 0;
	mConnectionState  = DREAMSOCK_CONNECTING;

	SetSocketAddress(address);

	//register this client with server
	mServer->addClient(this);

	//login
	mLoggedIn = false;
	
	LogString("create c++/java client");
}

//server side client constructor, many instances will be made, one for each client connected.
Client::Client(Server* server, struct sockaddr *address, int clientID)
{
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

	LogString("create browser client");
}

Client::~Client()
{
	mServer->mNetwork->dreamSock_CloseSocket(mServer->mNetwork->mSocket);
}

void Client::createShape()
{
	//create the shape for this client -- the avatar
	mShape = new Shape(mServer->mGame->getOpenIndex(),mServer->mGame,this,new Vector3D(),new Vector3D(),new Vector3D(),mServer->mGame->mRoot,true,true,.66f,1,false); 
	
	mShape->sendShapeToClients();
}

void Client::remove()
{
	for (unsigned int i = 0; i < mServer->mClientVector.size(); i++)
	{
		if (mServer->mClientVector.at(i) == this)
		{
			mShape->remove();
			mServer->mClientVector.erase(mServer->mClientVector.begin()+i);
		}
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

void Client::sendQuestion()
{
	//generate question based on level etc
	
	
	//send it
	//SendPacket(...
//	you could actually just SendPacket in writeQuestion and writeQuestionBrowser because we are not looping
//but we will not because it confuses this.
}

void Client::writeQuestion()
{

}

void Client::writeQuestionBrowser()
{
/*
        mGame->mServer->mMessage.Init(mGame->mServer->mMessage.outgoingData, sizeof(mGame->mServer->mMessage.outgoingData));

        mGame->mServer->mMessage.WriteByte(mGame->mServer->mAddShape); // type

        mGame->mServer->mMessage.WriteByte(client->mClientID); //client id for browsers

        if (client == mClient)
        {
                mGame->mServer->mMessage.WriteByte(1);
        }
        else
        {
                mGame->mServer->mMessage.WriteByte(0);
        }
        mGame->mServer->mMessage.WriteByte(mIndex);

        mGame->mServer->mMessage.WriteFloat(mSceneNode->getPosition().x);
        LogString("x:%f",mSceneNode->getPosition().x);
        mGame->mServer->mMessage.WriteFloat(mSceneNode->getPosition().y);
        mGame->mServer->mMessage.WriteFloat(mSceneNode->getPosition().z);

        mGame->mServer->mMessage.WriteFloat(mRotation->x);
        mGame->mServer->mMessage.WriteFloat(mRotation->z);

        //mesh
        mGame->mServer->mMessage.WriteByte(mMeshCode);

        //animation
        mGame->mServer->mMessage.WriteByte(mAnimated);
*/
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


