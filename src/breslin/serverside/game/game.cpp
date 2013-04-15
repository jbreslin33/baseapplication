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

#include <stdio.h>

Game::Game(Ogre::Root* root)
{
	mRoot = root;

	mBounds = new Bounds();
}

Game::~Game()
{
	StopLog();
	delete mServer;
}

//you should call this from server processUpdate
void Game::processUpdate()
{
	//this is where they want to move
	for (unsigned int i = 0; i < mShapeVector.size(); i++)
	{
		mShapeVector.at(i)->processTick();
		checkBounds(mShapeVector.at(i));
	}
	
	//this is where they can move..	
	checkCollisions();
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

//this is the whole shabang server exit not a player or shape exit
void Game::sendExitNotification()
{
	for (unsigned int i = 0; i < mServer->mClientVector.size(); i++)
	{

		mServer->mMessage.Init(mServer->mMessage.outgoingData,
			sizeof(mServer->mMessage.outgoingData));

		mServer->mMessage.WriteByte(mMessageServerExit);	// type
		mServer->mMessage.WriteShort(mServer->mOutgoingSequence);
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

Vector3D* Game::getOpenPoint()
{
	Vector3D* vector3D = new Vector3D();

	for (int x = 25; x < 400; x++)
	{	
		bool occupied = false; 
		vector3D->x = x;
		vector3D->y = 0;
		vector3D->z = 100;

                if (mShapeVector.size() < 1)
		{
			LogString("return default"); 
			return vector3D;
		}

                for (unsigned int i = 0; i < mShapeVector.size(); i++)
                {
                	if (mShapeVector.at(i)->mCollidable == true)
                        {
                        	float x1 = vector3D->x;
                                float z1 = vector3D->z;
                                float x2 = mShapeVector.at(i)->mSceneNode->getPosition().x;
                                float z2 = mShapeVector.at(i)->mSceneNode->getPosition().z;

                                float distSq = pow((x1-x2),2) + pow((z1-z2),2);

                                //i am simply adding the 2 collisionradius's of the 2 objects in question then comparing
                                //to distSQ between them. IS this right or is it working by chance?
                                if(distSq < mShapeVector.at(i)->mCollisionRadiusSpawn * 2)
                                {
					occupied = true; 
                                }
                        }
                }

		if (!occupied)
		{
			LogString("return modified"); 
			return vector3D;
		}
        }
}
