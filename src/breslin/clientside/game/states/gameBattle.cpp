//header
#include "gameBattle.h"

//log
#include "../../tdreamsock/dreamSockLog.h"

//application
#include "../../application/applicationBreslin.h"

//game
#include "../game.h"

//state machine
#include "../../../statemachine/stateMachine.h"

/***************************************
*	CONSTRUCTORS		          
***************************************/
GameBattle::GameBattle(Game* game)
{
	mGame = game;
}

GameBattle::~GameBattle()
{

}

void GameBattle::enter()
{
	
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
