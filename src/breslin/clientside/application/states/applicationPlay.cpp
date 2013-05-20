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
ApplicationPlay::ApplicationPlay(ApplicationBreslin* application)
{
	mApplication = application;
}

ApplicationPlay::~ApplicationPlay()
{

}

void ApplicationPlay::enter()
{
        mApplication->mPlayingGame = true;
        mApplication->mSentLeaveGame = false;
}
void ApplicationPlay::execute()
{
  	//check for logout as well....
        if (this->mApplication->mLoggedIn == false)
        {
                this->mApplication->mStateMachine->changeState(this->mApplication->mApplicationLogin);
        }

	if (mApplication->getKeyboard()->isKeyDown(OIS::KC_ESCAPE) && mApplication->mSentLeaveGame == false)
	{
		//send quit game
        	ByteBuffer* byteBuffer = new ByteBuffer();
        	byteBuffer->WriteByte(mApplication->mGame->mMessageQuitGame);
        	mApplication->mNetwork->send(byteBuffer);

                mApplication->mSentLeaveGame = true;
	}

	if (mApplication->mLeaveGame)
       	{
               	mApplication->mSentLeaveGame = false;
               	if (mApplication->mLoggedIn)
               	{
                       	mApplication->mStateMachine->changeState(mApplication->mApplicationMain);
               	}
               	else
               	{
                       	mApplication->mStateMachine->changeState(mApplication->mApplicationLogin);
               	}
       	}
       	else
       	{
              	//game
		if (mApplication->mGame)
		{	
               		mApplication->mGame->processUpdate();
		}
	}
}

void ApplicationPlay::exit()
{
	mApplication->mPlayingGame = false;
        mApplication->mLeaveGame = false;
        mApplication->mGame->remove();
	mApplication->mGame = NULL;
}
