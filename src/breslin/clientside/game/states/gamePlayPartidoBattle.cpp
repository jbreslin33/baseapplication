//header
#include "gamePlayPartidoBattle.h"

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
GamePlayPartidoBattle::GamePlayPartidoBattle(GamePartido* game)
{
	mGame = game;
}

GamePlayPartidoBattle::~GamePlayPartidoBattle()
{

}

void GamePlayPartidoBattle::enter()
{
	mGame->mBattleStart = false;
}
void GamePlayPartidoBattle::execute()
{

	//user input
	mGame->processInput();	
	
	//network outgoing
	mGame->sendByteBuffer();
}

void GamePlayPartidoBattle::exit()
{
	
}
