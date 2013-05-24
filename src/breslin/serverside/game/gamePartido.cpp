#include "gamePartido.h"

//log
#include "../tdreamsock/dreamSockLog.h"

//server
#include "../server/serverPartido.h"

//shape
#include "../shape/shapePartido.h"

//battles
#include "../battle/battle.h"

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
	
	//process Battles	
	for (unsigned int i = 0; i < mBattleVector.size(); i++)
        {
                mBattleVector.at(i)->processUpdate();
        }
}

void GamePartido::createShapes()
{
        for (unsigned int i = 0; i < mServerPartido->mClientVector.size(); i++)
        {
                mServerPartido->mClientPartidoVector.at(i)->setShape( new ShapePartido(getOpenIndex(),this,mServerPartido->mClientPartidoVector.at(i),getOpenPoint(),new Vector3D(),new Vector3D(),mServerPartido->mRoot,true,true,30.0f,1,false) );
        }
}


void GamePartido::collision(Shape* shape1, Shape* shape2)
{
	Game::collision(shape1,shape2);	

	//now let's check if these guys are already in a battle
	for (unsigned int i = 0; i < mBattleVector.size(); i++)
	{
		for (unsigned int s = 0; s < mBattleVector.at(i)->mShapePartidoVector.size(); s++)
		{
			if (shape1 == mBattleVector.at(i)->mShapePartidoVector.at(s) || shape2 == mBattleVector.at(i)->mShapePartidoVector.at(s))
			{
				return;
			} 
		}
	}
	
	battleCollision((ShapePartido*)shape1,(ShapePartido*)shape2);
}

void GamePartido::battleCollision(ShapePartido* shapePartido1, ShapePartido* shapePartido2)
{
	std::vector<ShapePartido*> shapePartidoVector;
	shapePartidoVector.push_back(shapePartido1);
	shapePartidoVector.push_back(shapePartido2);

	//create a battle
	Battle* battle = new Battle(this,shapePartidoVector);
	mBattleVector.push_back(battle);
}

void GamePartido::sendAnswer(ClientPartido* client, int answerTime, std::string answer)
{
	LogString("GamePartido::sendAnswer");
}
