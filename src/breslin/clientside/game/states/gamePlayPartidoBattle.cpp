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
	//reset text box 
	mGamePartido->mApplicationPartido->mStringAnswer.clear();
        mGamePartido->mApplicationPartido->mLabelQuestion->setCaption("");
        mGamePartido->mApplicationPartido->mLabelAnswer->setCaption("");
	
	mGamePartido->mApplicationPartido->showBattleScreen();
	mGamePartido->mBattleStart = false;

       
	//set mKeyArray to false 
	for (int i = 0; i < 128; i++)
	{
        	mGamePartido->mApplicationPartido->mKeyArray[i] = false;
	}
	mFirstTimeExecute = true;
}

void GamePlayPartidoBattle::execute()
{
 	if (mGamePartido->mBattleEnd)
        {
		LogString("battle end!!!");
                mGamePartido->mStateMachine->changeState(mGamePartido->mGamePlay); 
        }

	ApplicationPartido* app = mGamePartido->mApplicationPartido;


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
		
		if (app->mKeyArray[13]) //enter
                {
                        app->mKeyArray[13] = false;
                        app->sendAnswer();
                        app->mStringAnswer.clear();
                        app->mLabelAnswer->setCaption("");
                        app->mLabelAnswer->setCaption("");


                }

                for (int i = 47; i < 123; i++)
                {
                        if (app->mKeyArray[i])
                        {
				LogString("mKeyArray:%d",i);
                                app->mKeyArray[i] = false;
                                char ascii = (char)i;
                                app->mStringAnswer.append(1,ascii);
                                app->mLabelAnswer->setCaption(app->mStringAnswer);
                        }
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
	mGamePartido->mApplicationPartido->mStringAnswer.clear();
        mGamePartido->mApplicationPartido->mLabelQuestion->setCaption("");
        mGamePartido->mApplicationPartido->mLabelAnswer->setCaption("");
}
