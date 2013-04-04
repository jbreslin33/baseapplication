#include "game.h"

//log
#include "../tdreamsock/dreamSockLog.h"

//server
#include "../server/server.h"

//network
#include "../network/network.h"

//client
#include "../client/client.h"

//shape
#include "../shape/shape.h"

//math
#include "../../math/vector3D.h"

//bounds
#include "../bounds/bounds.h"

//postgresql
#include <stdio.h>
//#include <postgresql/libpq-fe.h>


Game::Game()
{
	StartLog();

#ifdef _DEBUG
	mRoot = new Ogre::Root("plugins_d.cfg");
#else
	mRoot = new Ogre::Root("plugins.cfg");
#endif
	mTickLength = 32;	
	mFrameTime  = 0;
	mGameTime   = 0;
	mFrameTimeLast  = 0;

	//sequence
	mOutgoingSequence = 1;

	mBounds = new Bounds();

	mDBConnection = PQconnectdb("dbname=abcandyou host=localhost user=postgres password=mibesfat");	
}

Game::~Game()
{
        PQfinish(mDBConnection);
	StopLog();
	delete mServer;
}

void Game::createServer()
{
	mServer = new Server(this,"", 30004);
}

void Game::createWorld()
{
  	for(int i = 0; i < 0; i++)
        {
                Vector3D* position = new Vector3D();
                position->x = 1.5f * i;
                position->y = 0.0f;
                position->z = 1.5f * i;

                Shape* shape = new Shape(getOpenIndex(),this,0,position,new Vector3D(),new Vector3D(),
                        mRoot,true,true,.66f,1,true);

	}
}

void Game::frame(int msec)
{
	mFrameTime += msec;
	mGameTime += msec;
	
	mServer->readPackets();

	//this is where they want to move
	for (unsigned int i = 0; i < mShapeVector.size(); i++)
	{
		mShapeVector.at(i)->processTick();
		checkBounds(mShapeVector.at(i));
	}
	
	//this is where they can move..	
	checkCollisions();
	
	// Wait full 32 ms before allowing to send
	if(mFrameTime < mTickLength)
	{
		return;
	}
	
	//send positions and exact frame time the calcs where done on which is mFrameTime 
	sendCommand();

	mFrameTimeLast = mFrameTime;
	mFrameTime = 0;

	checkForEndOfGame();
}

void Game::checkCollisions()
{
	for (unsigned int i = 0; i < mShapeVector.size(); i++)
	{
	  
		if (mShapeVector.at(i)->mCollidable == true)
		{
			for (unsigned int j = i+1; j < mShapeVector.size(); j++) 
			{
				if (mShapeVector.at(j)->mCollidable == true)
				{
					float x1 = mShapeVector.at(i)->mSceneNode->getPosition().x;
					float z1 = mShapeVector.at(i)->mSceneNode->getPosition().z;
					float x2 = mShapeVector.at(j)->mSceneNode->getPosition().x;
					float z2 = mShapeVector.at(j)->mSceneNode->getPosition().z;

					float distSq = pow((x1-x2),2) + pow((z1-z2),2);
					
					//i am simply adding the 2 collisionradius's of the 2 objects in question then comparing
					//to distSQ between them. IS this right or is it working by chance?
					if(distSq < mShapeVector.at(i)->mCollisionRadius + mShapeVector.at(j)->mCollisionRadius)
					{
						collision(mShapeVector.at(i),mShapeVector.at(j));
					}
				}
			}
		}
	}
}

void Game::checkBounds(Shape* shape)
{

}

void Game::collision(Shape* shape1, Shape* shape2)
{
	float x3 = shape1->mPositionBeforeCollision->x;
	float z3 = shape1->mPositionBeforeCollision->z;
	float x4 = shape2->mPositionBeforeCollision->x;
	float z4 = shape2->mPositionBeforeCollision->z;

	shape1->mSceneNode->setPosition(x3,0.0,z3);
	shape2->mSceneNode->setPosition(x4,0.0,z4);
}

bool Game::checkScope(Client* client, Shape* shape)
{
	//let's check scop here...
	float x1 = client->mShape->mSceneNode->getPosition().x;  //clientshape
	float z1 = client->mShape->mSceneNode->getPosition().z;
	float x2 = shape->mSceneNode->getPosition().x;  //build shape
	float z2 = shape->mSceneNode->getPosition().z;

	float distSq = pow((x1-x2),2) + pow((z1-z2),2);
			
	if(distSq < 10000000.0)
	{
		return true;
	}
	else 
	{
		return false;
	}
}

void Game::sendCommand(void)
{
	// Fill messages..for all clients
	//standard initialize of mMessage for client in this case
	mServer->mMessage.Init(mServer->mMessage.outgoingData,
		sizeof(mServer->mMessage.outgoingData));

	//start filling said mMessage that belongs to client
	mServer->mMessage.WriteByte(mServer->mMessageFrame);			// type
	
	mServer->mMessage.WriteShort(mOutgoingSequence);

	//frame time	
	mServer->mMessage.WriteByte(mFrameTime);

	//this is where you need to actually loop thru the shapes not the clients but put write to client mMessage
	for (unsigned int j = 0; j < mShapeVector.size(); j++)
	{                         //the client to send to's message        //the shape command it's about
		mShapeVector.at(j)->addToMoveMessage(&mServer->mMessage);
	}

	mServer->sendPackets();
	
	// Store the sent command in 
	for (unsigned int i = 0; i < mServer->mGame->mShapeVector.size(); i++)
	{
		storeCommands(mServer->mGame->mShapeVector.at(i));
	}
}

void Game::storeCommands(Shape* shape)
{
	shape->mKeyLast = shape->mKey;

	shape->mPositionLast->convertFromVector3(shape->mSceneNode->getPosition());

	shape->mRotationLast->copyValuesFrom(shape->mRotation);
}

//this is the whole shabang server exit not a player or shape exit
void Game::sendExitNotification()
{
	for (unsigned int i = 0; i < mServer->mClientVector.size(); i++)
	{

		mServer->mMessage.Init(mServer->mMessage.outgoingData,
			sizeof(mServer->mMessage.outgoingData));

		mServer->mMessage.WriteByte(mMessageServerExit);	// type
		mServer->mMessage.WriteShort(mOutgoingSequence);
	}

	mServer->sendPackets();
}

//this is just for clients right now, should i make another or hijack this function??
void Game::readDeltaMoveCommand(Message *mes, Client *client)
{
	client->mShape->mKey = mes->ReadByte();
}

unsigned int Game::getOpenIndex()
{
	bool proposedIndexOpen = false;
	for (unsigned int proposedIndex = 1; !proposedIndexOpen; proposedIndex++) //keep going till you get an index
	{
		bool someoneHasThisIndex = false;
		for (unsigned int i = 0; i < mShapeVector.size(); i++)
		{
			if (mShapeVector.at(i)->mIndex == proposedIndex)
			{
				someoneHasThisIndex = true;
			}
		}
		if (someoneHasThisIndex == false)
		{
			return  proposedIndex;
		}
	}
	return 0;
}
