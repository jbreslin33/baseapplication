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
	//server
	mServer = server;

	mLastMessageTime  = 0;
	mConnectionState  = DREAMSOCK_CONNECTING;
	mOutgoingSequence = 1;
	mIncomingSequence = 0;

	SetSocketAddress(address);

	//register this client with server
	mServer->addClient(this);
}

Client::~Client()
{
	mServer->mNetwork->dreamSock_CloseSocket(mServer->mNetwork->mSocket);
	//delete mNetwork;
}

void Client::sendConnect()
{
	//send a connect message
	mMessage.Init(mMessage.outgoingData, sizeof(mMessage.outgoingData));
	mMessage.WriteByte(mServer->mConnect);	// type
	SendPacket(&mMessage);
}

void Client::createShape()
{
	//create the shape for this client -- the avatar
	mShape = new Shape(mServer->mGame->getOpenIndex(),mServer->mGame,this,new Vector3D(),new Vector3D(),new Vector3D(),mServer->mGame->mRoot,true,true,.66f,1,false); 
	
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
			SendPacket(&mMessage);
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
		mOutgoingSequence++;
	}
}


