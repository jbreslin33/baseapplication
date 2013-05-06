//header
#include "gamePlayPartidoBattle.h"

//log
#include "../../tdreamsock/dreamSockLog.h"

//application
#include "../../application/applicationPartido.h"

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
	LogString("GamePlayPartidoBattle::enter");
	mGame->mApplication->createBattleScreen();
	mGame->mApplication->showBattleScreen();
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
	mGame->mApplication->hideBattleScreen();
	mGame->mBattleEnd = true;
}
