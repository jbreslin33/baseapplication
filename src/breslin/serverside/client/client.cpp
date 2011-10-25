#include "client.h"
#include "../tdreamsock/dreamSockLog.h"

#include "../../serverside/network/network.h"
#include "../../serverside/server/server.h"
#include "../../serverside/game/game.h"
#include "../../serverside/shape/shape.h"

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
	mServer = server;

	SetSocketAddress(address);

	mLastMessageTime  = 0;
	mConnectionState  = DREAMSOCK_CONNECTING;
	mOutgoingSequence = 1;
	mIncomingSequence = 0;

	//register this client with server
	mServer->mClientVector.push_back(this);

	//send a connect message
	mMessage.Init(mMessage.outgoingData, sizeof(mMessage.outgoingData));
	mMessage.WriteByte(mServer->mConnect);	// type
	SendPacket(&mMessage);

	//create the shape for this client -- the avatar
	mShape = new Shape(mServer->mGame,this,new Vector3D(),new Vector3D(),new Vector3D(),mServer->mGame->mRoot,true,true,.66f,1,false); 
		
	//let this client know about all shapes(it will sending add for it's avatar as that is done right above.)
	sendAllShapes();
}

Client::~Client()
{
	mServer->mNetwork->dreamSock_CloseSocket(mServer->mNetwork->mSocket);
	//delete mNetwork;
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
			mServer->mGame->mShapeVector.at(i)->write(this);
		
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


