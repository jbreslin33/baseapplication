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
}

GamePlayPartido::~GamePlayPartido()
{

}

void GamePlayPartido::enter()
{
	GamePlay::enter();
}
void GamePlayPartido::execute()
{
	GamePlay::execute();
	if (mGame->mBattleStart)
	{
		mGame->mStateMachine->changeState(mGame->mGamePlayPartidoBattle);		
	}

	//user input
	mGame->processInput();	
	
	//network outgoing
	mGame->sendByteBuffer();
}

void GamePlayPartido::exit()
{
	GamePlay::exit();
}
