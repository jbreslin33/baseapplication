//header
#include "gamePlayPartidoReset.h"

//log
#include "../../tdreamsock/dreamSockLog.h"

//application
#include "../../application/applicationPartido.h"

//game
#include "../gamePartido.h"

//byte buffer
#include "../../bytebuffer/byteBuffer.h"

//network
#include "../../network/network.h"

//state machine
#include "../../../statemachine/stateMachine.h"

/***************************************
*	CONSTRUCTORS		          
***************************************/
GamePlayPartidoReset::GamePlayPartidoReset(GamePartido* gamePartido)
{
	mGamePartido = gamePartido;
}

GamePlayPartidoReset::~GamePlayPartidoReset()
{

}

void GamePlayPartidoReset::enter()
{
	LogString("GamePlayPartidoReset::enter");
/*
	ApplicationPartido* app = mGamePartido->mApplicationPartido;

	app->showCorrectAnswerScreen();
	mGamePartido->mCorrectAnswerStart = false;
*/
}

void GamePlayPartidoReset::execute()
{
	ApplicationPartido* app = mGamePartido->mApplicationPartido;
/*
 	if (mGamePartido->mCorrectAnswerEnd)
        {
                mGamePartido->mStateMachine->changeState(mGamePartido->mGamePlayPartidoBattle); 
        }

        if (mGamePartido->mBattleEnd)
        {
                mGamePartido->mStateMachine->changeState(mGamePartido->mGamePlayPartidoBattle);
        }
 */       
	if (!mGamePartido->mApplicationPartido->mGameReset)
        {
                mGamePartido->mStateMachine->changeState(mGamePartido->mGamePlay);
        }
}

void GamePlayPartidoReset::exit()
{
//	if (!mGamePartido->mApplicationPartido->mGameReset)
/*
	mGamePartido->mApplicationPartido->hideCorrectAnswerScreen();
	mGamePartido->mCorrectAnswerStart = false;
	mGamePartido->mCorrectAnswer      = false;
	mGamePartido->mCorrectAnswerEnd   = false;
	
	//reset text box 
	mGamePartido->mApplicationPartido->mStringCorrectAnswer.clear();
        mGamePartido->mApplicationPartido->mLabelCorrectAnswer->setCaption("");
*/
}
