//header
#include "gamePartidoPlay.h"

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
GamePartidoPlay::GamePartidoPlay(GamePartido* game) : GamePlay(game)
{
	mGame = game;
}

GamePartidoPlay::~GamePartidoPlay()
{

}

void GamePartidoPlay::enter()
{
	
}
void GamePartidoPlay::execute()
{
	if (mGame->mBattleStart)
	{
		mGame->mStateMachine->changeState(mGame->mGameBattle);		
	}

	//user input
	mGame->processInput();	
	
	//network outgoing
	mGame->sendByteBuffer();
}

void GamePartidoPlay::exit()
{
	
}
