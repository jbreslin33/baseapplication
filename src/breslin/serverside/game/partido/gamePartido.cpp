#include "gamePartido.h"

//log
#include "../../tdreamsock/dreamSockLog.h"

//server
#include "../../server/partido/serverPartido.h"

//shape
#include "../../shape/partido/shapePartido.h"

//client
#include "../../client/robust/partido/clientPartido.h"

//vector3d
#include "../../../math/vector3D.h"

#include <stdio.h>

GamePartido::GamePartido(ServerPartido* serverPartido, int id) : Game(serverPartido,id)
{
	mServerPartido = serverPartido;
}

GamePartido::~GamePartido()
{
}

//you should call this from server update
void GamePartido::update()
{
	Game::update();
	
	if (checkForEndOfGame())
	{
		LogString("endOFGAME!!!!!!!!!!!!!!!!!!!!!!");
		reset();		
	}
}

void GamePartido::sendShapes(ClientPartido* clientPartido)
{
	Game::sendShapes(clientPartido);
}

void GamePartido::reset()
{
        for (unsigned int i = 0; i < mServerPartido->mClientPartidoVector.size(); i++)
	{
		ClientPartido* clientPartido = mServerPartido->mClientPartidoVector.at(i);
		if (clientPartido->mClientID == -1) //browser bridge
		{
			continue;
		}

		//reset opponent pointers	
		clientPartido->resetOpponents();
		
		//collision
        	clientPartido->mShapePartido->mCollidable = true; 
	
		//is anyone in a battle as game ends?	
   		if (clientPartido->mConnectionState == DREAMSOCK_CONNECTED)
		{
			clientPartido->sendBattleEnd();	
		}	
			
		clientPartido->mBattleScore = 0;	

		clientPartido->resetRecords();	

		clientPartido->setBattleRecordText();	
	}

}

bool GamePartido::checkForEndOfGame()
{
	//check for end of game
        for (unsigned int i = 0; i < mServerPartido->mClientPartidoVector.size(); i++)
	{
		if (mServerPartido->mClientPartidoVector.at(i)->mClientID == -1) //browser bridge
		{
			continue;
		}

		if (mServerPartido->mClientPartidoVector.at(i)->mLosses == 0)	
		{
			return false;
		}
		else
		{
		}
	}
	
	return true;
}

void GamePartido::createShapes()
{
        for (unsigned int i = 0; i < mServerPartido->mClientPartidoVector.size(); i++)
        {
                mServerPartido->mClientPartidoVector.at(i)->setShape( new ShapePartido(getOpenIndex(),this,mServerPartido->mClientPartidoVector.at(i),getOpenPoint(),new Vector3D(),new Vector3D(),mServerPartido->mRoot,false,true,30.0f,1,true) );

        }
}

void GamePartido::checkCollisions()
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

