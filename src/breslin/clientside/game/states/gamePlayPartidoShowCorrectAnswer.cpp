//header
#include "gamePlayPartidoShowCorrectAnswer.h"

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
GamePlayPartidoShowCorrectAnswer::GamePlayPartidoShowCorrectAnswer(GamePartido* gamePartido)
{
	mGamePartido = gamePartido;
	mFirstTimeExecute = true;
}

GamePlayPartidoShowCorrectAnswer::~GamePlayPartidoShowCorrectAnswer()
{

}

void GamePlayPartidoShowCorrectAnswer::enter()
{
	LogString("GamePlayPartidoShowCorrectAnswer::enter");
	ApplicationPartido* app = mGamePartido->mApplicationPartido;

	//reset text box 
	//app->mStringCorrectAnswer.clear();
        //app->mLabelCorrectAnswer->setCaption("");
	
	app->showCorrectAnswerScreen();
	mGamePartido->mCorrectAnswerStart = false;
}

void GamePlayPartidoShowCorrectAnswer::execute()
{
	ApplicationPartido* app = mGamePartido->mApplicationPartido;

 	if (mGamePartido->mCorrectAnswerEnd)
        {
                mGamePartido->mStateMachine->changeState(mGamePartido->mGamePlayPartidoBattle); 
        }
}

void GamePlayPartidoShowCorrectAnswer::exit()
{
	mGamePartido->mApplicationPartido->hideCorrectAnswerScreen();
	mGamePartido->mCorrectAnswerStart = false;
	mGamePartido->mCorrectAnswer      = false;
	mGamePartido->mCorrectAnswerEnd   = false;
	
	//reset text box 
	mGamePartido->mApplicationPartido->mStringCorrectAnswer.clear();
        mGamePartido->mApplicationPartido->mLabelCorrectAnswer->setCaption("");
}
