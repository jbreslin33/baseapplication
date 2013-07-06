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

Game::Game(Server* server, int id)
{
	//id
	mID = id; 

	//server
	mServer = server;

	//bounds
	mBounds = new Bounds();
   	mBounds->a = new Vector3D(-250.0f,0.0f,-250.0f);
        mBounds->c = new Vector3D(250.0f,0.0f,250.0f);

}

Game::~Game()
{
	StopLog();
	delete mServer;
}

void Game::createShapes()
{
        for (unsigned int i = 0; i < mServer->mClientVector.size(); i++)
        {
                mServer->mClientVector.at(i)->setShape( new Shape(getOpenIndex(),this,mServer->mClientVector.at(i),getOpenPoint(),new Vector3D(),new Vector3D(),mServer->mRoot,true,true,30.0f,1,false) );
        }
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
						mShapeVector.at(i)->collision(mShapeVector.at(j));
						mShapeVector.at(j)->collision(mShapeVector.at(i));
					}
				}
			}
		}
	}
}

void Game::checkBounds(Shape* shape)
{
        if (shape->mSceneNode->getPosition().x < mBounds->a->x)
        {
                shape->mSceneNode->setPosition(mBounds->a->x, shape->mSceneNode->getPosition().y, shape->mSceneNode->getPosition().z);
        }

        if (shape->mSceneNode->getPosition().x > mBounds->c->x)
        {
                shape->mSceneNode->setPosition(mBounds->c->x, shape->mSceneNode->getPosition().y, shape->mSceneNode->getPosition().z);
        }


        if (shape->mSceneNode->getPosition().z < mBounds->a->z)
        {
                shape->mSceneNode->setPosition(shape->mSceneNode->getPosition().x, shape->mSceneNode->getPosition().y, mBounds->a->z);
        }

        if (shape->mSceneNode->getPosition().z > mBounds->c->z)
        {
                shape->mSceneNode->setPosition(shape->mSceneNode->getPosition().x, shape->mSceneNode->getPosition().y, mBounds->c->z);
        }
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

	for (int x = 25; x < 3000; x++)
	{	
		bool occupied = false; 
		vector3D->x = x;
		vector3D->y = 0;
		vector3D->z = 35;

                if (mShapeVector.size() < 1)
		{
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
                                if(distSq < mShapeVector.at(i)->mCollisionRadiusSpawn * 25)
                                {
					occupied = true; 
                                }
                        }
                }

		if (!occupied)
		{
			return vector3D;
		}
        }
}

void Game::sendShapes(Client* client)
{
 	for (unsigned int i = 0; i < mShapeVector.size(); i++)
        {
  		mMessage.Init(mMessage.outgoingData, sizeof(mMessage.outgoingData));

        	mMessage.WriteByte(mServer->mMessageAddShape); // type

        	if (client->mClientID > 0)
        	{
                	mMessage.WriteByte(client->mClientID); //client id for browsers
        	}
                
        	if (client == mShapeVector.at(i)->mClient)
        	{       
                	mMessage.WriteByte(1);
        	}               
        	else    
        	{       
                	mMessage.WriteByte(0);
        	}
        	mMessage.WriteByte(mShapeVector.at(i)->mIndex);

        	mMessage.WriteFloat(mShapeVector.at(i)->mSceneNode->getPosition().x);
        	mMessage.WriteFloat(mShapeVector.at(i)->mSceneNode->getPosition().y);
        	mMessage.WriteFloat(mShapeVector.at(i)->mSceneNode->getPosition().z);

        	mMessage.WriteFloat(mShapeVector.at(i)->mRotationBres->x);
        	mMessage.WriteFloat(mShapeVector.at(i)->mRotationBres->z);

        	//mesh
        	mMessage.WriteByte(mShapeVector.at(i)->mMeshCode);

        	//animation
        	mMessage.WriteByte(mShapeVector.at(i)->mAnimated);

        	//essentially should be setText...previously username...
        	int length = mShapeVector.at(i)->mText.length(); 
        	mMessage.WriteByte(length); //send length
		
        	//loop thru length and write it
        	for (int b=0; b < length; b++)
        	{
                	mMessage.WriteByte(mShapeVector.at(i)->mText.at(b));
        	}

                //send it
                mServer->mNetwork->sendPacketTo(client,&mMessage);
        }
}



//the client that is leaving????
void Game::leave(Client* client)
{
        if (client->mShape)
        {
  		mMessage.Init(mMessage.outgoingData, sizeof(mMessage.outgoingData));
                mMessage.Init(mMessage.outgoingData, sizeof(mMessage.outgoingData));
                mMessage.WriteByte(mServer->mMessageLeaveGame); // add type
                if (client->mClientID > 0)
                {
                        mMessage.WriteByte(client->mClientID); //client id for browsers
                }
                mServer->mNetwork->sendPacketTo(client,&mMessage);
        }
        client->mGame = NULL;
}

