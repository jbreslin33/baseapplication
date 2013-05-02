//header
#include "gameBattle.h"

//log
#include "../../tdreamsock/dreamSockLog.h"

//application
#include "../../application/applicationBreslin.h"

//game
#include "../gamePartido.h"

//state machine
#include "../../../statemachine/stateMachine.h"

/***************************************
*	CONSTRUCTORS		          
***************************************/
GameBattle::GameBattle(GamePartido* game)
{
	mGame = game;
}

GameBattle::~GameBattle()
{

}

void GameBattle::enter()
{
	LogString("GameBattle state enter");	
	mGame->mBattleStart = false;
}
void GameBattle::execute()
{
	//user input
	mGame->processInput();	
	
	//network outgoing
	mGame->sendByteBuffer();
}

void GameBattle::exit()
{
	
}
