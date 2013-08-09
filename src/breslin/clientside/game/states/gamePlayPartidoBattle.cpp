//header
#include "gamePlayPartidoBattle.h"

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
GamePlayPartidoBattle::GamePlayPartidoBattle(GamePartido* gamePartido)
{
	mGamePartido = gamePartido;
	mFirstTimeExecute = true;
}

GamePlayPartidoBattle::~GamePlayPartidoBattle()
{

}

void GamePlayPartidoBattle::enter()
{
	ApplicationPartido* app = mGamePartido->mApplicationPartido;

	//reset text box 
	app->mStringAnswer.clear();
        app->mLabelQuestion->setCaption("");
        app->mLabelAnswer->setCaption("");
	
	app->showBattleScreen();
	mGamePartido->mBattleStart = false;
      
	app->mAnswerTime = 0;
 
	//set mKeyArray to false 
	for (int i = 0; i < 128; i++)
	{
        	mGamePartido->mApplicationPartido->mKeyArray[i] = false;
	}
	mFirstTimeExecute = true;
}

void GamePlayPartidoBattle::execute()
{
	ApplicationPartido* app = mGamePartido->mApplicationPartido;

	if (app->mAnswerTime > 2000) //overtime....
	{
		app->mStringAnswer = "oot";		
		app->sendAnswer();
	}

 	if (mGamePartido->mBattleEnd)
        {
                mGamePartido->mStateMachine->changeState(mGamePartido->mGamePlay); 
        }


	if (mFirstTimeExecute)
	{
		for (int i = 0; i < 128; i++)
		{
        		mGamePartido->mApplicationPartido->mKeyArray[i] = false;
		}
		mFirstTimeExecute = false;
	}

	if (app->mLabelFocus == app->mLabelAnswer)
	{
        	if (app->mKeyArray[8]) //backspace
                {
                        app->mKeyArray[8] = false;
                        int size = app->mStringAnswer.size();
                        if (size > 0)
                        {
                                app->mStringAnswer.resize(size - 1);
                        }
                        app->mLabelAnswer->setCaption(app->mStringAnswer);
                }

                for (int i = 47; i < 123; i++)
                {
                        if (app->mKeyArray[i])
                        {
                                app->mKeyArray[i] = false;
                                char ascii = (char)i;
                                app->mStringAnswer.append(1,ascii);
                                app->mLabelAnswer->setCaption(app->mStringAnswer);
                        }
                }
		
		if (app->mKeyArray[13]) //enter
                {
                        app->mKeyArray[13] = false;
                        app->sendAnswer();
                        app->mStringQuestion.clear();
                        app->mStringAnswer.clear();
                        app->mLabelQuestion->setCaption("");
                        app->mLabelAnswer->setCaption("");
                }
	
		//set mKeyArray to false 
		for (int i = 0; i < 128; i++)
		{
        		mGamePartido->mApplicationPartido->mKeyArray[i] = false;
		}

	}
}

void GamePlayPartidoBattle::exit()
{
	mGamePartido->mApplicationPartido->hideBattleScreen();
	mGamePartido->mBattleEnd   = false;
	mGamePartido->mBattleStart = false;
	
	//reset text box 
	mGamePartido->mApplicationPartido->mStringQuestion.clear();
	mGamePartido->mApplicationPartido->mStringAnswer.clear();
        mGamePartido->mApplicationPartido->mLabelQuestion->setCaption("");
        mGamePartido->mApplicationPartido->mLabelAnswer->setCaption("");
}
