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

	mShapePartidoVector = new std::vector<ShapePartido*>();
}

GamePartido::~GamePartido()
{
	LogString("GamePartido::~GamePartido");
	//delete shapePartidos
        while (!mShapePartidoVector->empty())
        {
		LogString("delete shapePartido in ~GamePartido");
                mShapePartidoVector->front() = NULL;
                delete mShapePartidoVector->front();
                mShapePartidoVector->erase(mShapePartidoVector->begin());
        }
        delete mShapePartidoVector;
}

//you should call this from server update
void GamePartido::update()
{
	Game::update();
/*	
	if (checkForEndOfGame())
	{
		//LogString("endOFGAME!!!!!!!!!!!!!!!!!!!!!!");
		//reset();		
	}
*/
}

void GamePartido::sendShapes(ClientPartido* clientPartido)
{
	Game::sendShapes(clientPartido);
}

void GamePartido::reset()
{
        for (unsigned int i = 0; i < mServerPartido->mClientPartidoVector->size(); i++)
	{
		ClientPartido* clientPartido = mServerPartido->mClientPartidoVector->at(i);
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
        for (unsigned int i = 0; i < mServerPartido->mClientPartidoVector->size(); i++)
	{
		if (mServerPartido->mClientPartidoVector->at(i)->mClientID == -1) //browser bridge
		{
			continue;
		}

		if (mServerPartido->mClientPartidoVector->at(i)->mLosses == 0)	
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
        for (unsigned int i = 0; i < mServerPartido->mClientPartidoVector->size(); i++)
        {
                mServerPartido->mClientPartidoVector->at(i)->setShape( new ShapePartido(getOpenIndex(),this,mServerPartido->mClientPartidoVector->at(i),getOpenPoint(),new Vector3D(),new Vector3D(),mServerPartido->mRoot,true,true,30.0f,1,true) );

        }
}
