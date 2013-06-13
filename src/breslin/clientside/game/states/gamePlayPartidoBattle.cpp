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
}

GamePlayPartidoBattle::~GamePlayPartidoBattle()
{

}

void GamePlayPartidoBattle::enter()
{
	LogString("GamePlayPartidoBattle::enter");
	mGamePartido->mApplicationPartido->createBattleScreen();
	mGamePartido->mApplicationPartido->showBattleScreen();
	mGamePartido->mBattleStart = false;

	//reset text box 
	mGamePartido->mApplicationPartido->mStringAnswer.clear();
        mGamePartido->mApplicationPartido->mLabelAnswer->setCaption("");
       
	//set mKeyArray to false 
	for (int i = 0; i < 128; i++)
	{
        	mGamePartido->mApplicationPartido->mKeyArray[i] = false;
	}
}

void GamePlayPartidoBattle::execute()
{
 	if (mGamePartido->mBattleEnd)
        {
		LogString("battle end!!!");
                mGamePartido->mStateMachine->changeState(mGamePartido->mGamePlay); 
        }

	ApplicationPartido* app = mGamePartido->mApplicationPartido;



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
                        app->mLabelAnswer->setCaption(app->mStringAnswer);
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
/*	
if (mApplication->mLabelFocus == mApplication->mLabelUsername)
        {

                if (mApplication->mKeyArray[8]) //backspace
                {
                        mApplication->mKeyArray[8] = false;
                        int size = mApplication->mStringUsername.size();
                        if (size > 0)
                        {
                                mApplication->mStringUsername.resize(size - 1);
                        }
                        mApplication->mLabelUsername->setCaption(mApplication->mStringUsername);
                }

                if (mApplication->mKeyArray[9]) //tab
                {
                        mApplication->mKeyArray[9] = false;
                        mApplication->mLabelFocus = mApplication->mLabelPassword;
                }

                if (mApplication->mKeyArray[13]) //enter
                {
                        mApplication->mKeyArray[13] = false;
                        mApplication->mLabelFocus = mApplication->mLabelPassword;
                }

                for (int i = 47; i < 123; i++)
                {
                        if (mApplication->mKeyArray[i])
                        {
                                mApplication->mKeyArray[i] = false;
                                char ascii = (char)i;
                                mApplication->mStringUsername.append(1,ascii);
                                mApplication->mLabelUsername->setCaption(mApplication->mStringUsername);
                        }
                }
        }

*/	
/*
 if (mLabelFocus == mLabelAnswer)
                {
                        int numeric = arg.text;
                        char ascii = (char)numeric;

                        if (numeric == 8) //backspace
                        {
                                int size = mStringAnswer.size();
                                if (size > 0)
                                {
                                        mStringAnswer.resize(size - 1);
                                }
                                mLabelAnswer->setCaption(mStringAnswer);
                        }

                        if (numeric == 13) //carriage return  or enter
                        {
                                sendAnswer();
                                mStringAnswer.clear();
                                mLabelAnswer->setCaption(mStringAnswer);
                        }

                        if (numeric > 47 && numeric < 123) //letters and valid symbols for username and password
                        {
                                mStringAnswer.append(1,ascii);
                                mLabelAnswer->setCaption(mStringAnswer);
                        }

                }      

*/
}

void GamePlayPartidoBattle::exit()
{
	mGamePartido->mApplicationPartido->hideBattleScreen();
	mGamePartido->mBattleEnd   = false;
	mGamePartido->mBattleStart = false;
}
