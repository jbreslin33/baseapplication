//header
#include "gamePlayPartido.h"

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
GamePlayPartido::GamePlayPartido(GamePartido* gamePartido) : GamePlay(gamePartido)
{
	mGamePartido = gamePartido;
}

GamePlayPartido::~GamePlayPartido()
{

}

void GamePlayPartido::enter()
{
	LogString("GamePlayPartido::enter");
	GamePlay::enter();
}
void GamePlayPartido::execute()
{
	if (mGamePartido->mBattleStart)
	{
		mGamePartido->mStateMachine->changeState(mGamePartido->mGamePlayPartidoBattle);		
	}

        if (mGamePartido->mApplicationPartido->mGameReset)
        {
                mGamePartido->mStateMachine->changeState(mGamePartido->mGamePlayPartidoReset);
        }

	GamePlay::execute();
}

void GamePlayPartido::exit()
{
	GamePlay::exit();
}
