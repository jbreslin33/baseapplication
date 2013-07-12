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

//rotation
#include "../rotation/rotation.h"

//move
#include "../move/move.h"

//math
#include "../../math/vector3D.h"

//states
#include "states/clientStates.h"

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

//quiz
#include "../quiz/quiz.h"

Client::Client(Server* server, struct sockaddr *address, int clientID, bool permanence) : BaseEntity(BaseEntity::getNextValidID())
{

	//client id for php but everyone uses one...
	mClientID = clientID;
	
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
		sendSchools();
	}
	else
	{
		//your the node for web sockets or a dummy ai client using node address temporarily
	}

      	if (!permanence)
        {
                mServer->addClient(this,false);
        }      

	mServer->mBaseEntityVector.push_back(this);

	//client states
	mClientStateMachine =  new StateMachine<Client>(this);
        mClientStateMachine->setCurrentState      (NULL);
        mClientStateMachine->setPreviousState     (NULL);
        mClientStateMachine->setGlobalState       (GlobalClient::Instance());
}

Client::~Client()
{
/*
	for (unsigned int i = 0; i < mServer->mClientVector.size(); i++)
        {
                if (mServer->mClientVector.at(i) == this)
		{
 			mServer->mClientVector.erase(mServer->mClientVector.begin()+i);
		}
	}
*/
}


void Client::setSocketAddress(struct sockaddr *address)
{
	memcpy(&mSocketAddress, address, sizeof(struct sockaddr)); 
}

void Client::update()
{
        mClientStateMachine->update();
}

bool Client::handleLetter(Letter* letter)
{
	return mClientStateMachine->handleLetter(letter);
}

void Client::remove()
{
/*
	for (unsigned int i = 0; i < mServer->mClientVector.size(); i++)
	{
		if (mServer->mClientVector.at(i) == this)
		{
			//mServer->mClientVector.erase(mServer->mClientVector.begin()+i);
			///delete this;
		}
	}
*/
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

void Client::checkForTimeout()
{
/*
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
*/
}

