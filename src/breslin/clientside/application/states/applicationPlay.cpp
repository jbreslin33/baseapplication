//header
#include "applicationPlay.h"

//log
#include "../../tdreamsock/dreamSockLog.h"

//application
#include "../applicationBreslin.h"

//game
#include "../../game/game.h"

//state machine
#include "../../../statemachine/stateMachine.h"

//byteBuffer
#include "../../bytebuffer/byteBuffer.h"

//byteBuffer
#include "../../network/network.h"

/***************************************
*	CONSTRUCTORS
***************************************/
ApplicationPlay::ApplicationPlay(ApplicationBreslin* applicationBreslin)
{
	mApplicationBreslin = applicationBreslin;
}

ApplicationPlay::~ApplicationPlay()
{

}

void ApplicationPlay::enter()
{
        mApplicationBreslin->mPlayingGame = true;
        mApplicationBreslin->mSentLeaveGame = false;
}
void ApplicationPlay::execute()
{
  	//check for logout as well....

        if (this->mApplicationBreslin->mLoggedIn == false )
        {
                this->mApplicationBreslin->mStateMachine->changeState(this->mApplicationBreslin->mApplicationLogin);
        }

/*	
	if (mApplicationBreslin->mKeyArray[27]) //esc
        {
		LogString("esc");
        	mApplicationBreslin->mKeyArray[27] = false;

		//send quit game
        	ByteBuffer* byteBuffer = new ByteBuffer();
        	byteBuffer->WriteByte(mApplicationBreslin->mMessageLeaveGame);
        	mApplicationBreslin->mNetwork->send(byteBuffer);
                mApplicationBreslin->mSentLeaveGame = true;
	}
*/
/*
	if (mApplication->getKeyboard()->isKeyDown(OIS::KC_ESCAPE) && mApplicationBreslin->mSentLeaveGame == false)
	{
		//send quit game
        	ByteBuffer* byteBuffer = new ByteBuffer();
        	byteBuffer->WriteByte(mApplicationBreslin->mGame->mMessageQuitGame);
        	mApplicationBreslin->mNetwork->send(byteBuffer);

                mApplicationBreslin->mSentLeaveGame = true;
	}
*/
	if (mApplicationBreslin->mLeaveGame)
       	{
		LogString("mLeaveGame true");
               	mApplicationBreslin->mSentLeaveGame = false;
               	if (mApplicationBreslin->mLoggedIn)
               	{
                       	mApplicationBreslin->mStateMachine->changeState(mApplicationBreslin->mApplicationMain);
               	}
               	else
               	{
                       	mApplicationBreslin->mStateMachine->changeState(mApplicationBreslin->mApplicationLogin);
               	}
       	}
       	else
       	{
              	//game
		if (mApplicationBreslin->mGame)
		{	
               		mApplicationBreslin->mGame->processUpdate();
		}
	}
}

void ApplicationPlay::exit()
{
	mApplicationBreslin->mPlayingGame = false;
        mApplicationBreslin->mLeaveGame = false;
	if (mApplicationBreslin->mGame)
	{
        	mApplicationBreslin->mGame->remove();
		mApplicationBreslin->mGame = NULL;
	}
}
