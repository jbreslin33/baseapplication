#include "gamePartido.h"

//log
#include "../tdreamsock/dreamSockLog.h"

//server
#include "../server/serverPartido.h"

//shape
#include "../shape/shapePartido.h"

//client
#include "../client/clientPartido.h"

//vector3d
#include "../../math/vector3D.h"

#include <stdio.h>

GamePartido::GamePartido(ServerPartido* serverPartido, int id) : Game(serverPartido,id)
{
	mServerPartido = serverPartido;
}

GamePartido::~GamePartido()
{
}

//you should call this from server processUpdate
void GamePartido::processUpdate()
{
	Game::processUpdate();
	
	if (checkForEndOfGame())
	{
		LogString("endOFGAME!!!!!!!!!!!!!!!!!!!!!!");
		reset();		
	}
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

   		//set your last opponent
        	clientPartido->mShapePartido->mOpponentLast = NULL; 

        	//clear you opponent
        	clientPartido->mShapePartido->mOpponent = NULL; 

		//collision
        	clientPartido->mShapePartido->mCollidable = NULL; 
		
   		if (clientPartido->mConnectionState == DREAMSOCK_CONNECTED)
		{
			clientPartido->sendBattleEnd();	
		}	
			
		clientPartido->mBattleScore = 0;	
		clientPartido->mWins   = 0;	
		clientPartido->mLosses = 0;	
		clientPartido->mTies   = 0;	

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
	}
	
	return true;
}

void GamePartido::createShapes()
{
        for (unsigned int i = 0; i < mServerPartido->mClientPartidoVector.size(); i++)
        {
                mServerPartido->mClientPartidoVector.at(i)->setShape( new ShapePartido(getOpenIndex(),this,mServerPartido->mClientPartidoVector.at(i),getOpenPoint(),new Vector3D(),new Vector3D(),mServerPartido->mRoot,true,true,30.0f,1,false) );
        }
}

void GamePartido::sendAnswer(ClientPartido* client, int answerTime, std::string answer)
{
	LogString("GamePartido::sendAnswer");
}
