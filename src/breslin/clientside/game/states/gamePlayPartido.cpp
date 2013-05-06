//header
#include "gamePlayPartido.h"

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
GamePlayPartido::GamePlayPartido(GamePartido* game) : GamePlay(game)
{
	mGame = game;
	LogString("GamePlayPartido::GamePlayPartido");
}

GamePlayPartido::~GamePlayPartido()
{

}

void GamePlayPartido::enter()
{
	GamePlay::enter();
	LogString("GamePlayPartido::enter");
}
void GamePlayPartido::execute()
{
	GamePlay::execute();
	if (mGame->mBattleStart)
	{
		mGame->mStateMachine->changeState(mGame->mGamePlayPartidoBattle);		
	}

	LogString("GamePlayPartido::execute");

	//user input
	mGame->processInput();	
	
	//network outgoing
	mGame->sendByteBuffer();
}

void GamePlayPartido::exit()
{
	GamePlay::exit();
}
