#include "gamePartido.h"

//log
#include "../tdreamsock/dreamSockLog.h"

//server
#include "../server/server.h"

//shape
#include "../shape/shapePartido.h"

//battles
#include "../battle/battle.h"

#include <stdio.h>

GamePartido::GamePartido(Server* server, int id) : Game(server,id)
{
	LogString("constructor for GamePartido");
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

void GamePartido::collision(Shape* shape1, Shape* shape2)
{
	//do regular collision of backing off shapes
	Game::collision(shape1,shape2);	

	//now let's check if these guys are already in a battle



	std::vector<Shape*> shapeVector;
	shapeVector.push_back(shape1);
	shapeVector.push_back(shape2);

	//create a battle
	Battle* battle = new Battle(this,shapeVector);
	mBattleVector.push_back(battle);
}
