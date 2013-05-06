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
	LogString("execute in ApplicationPlay begin");
	if (mApplication->getKeyboard()->isKeyDown(OIS::KC_ESCAPE) && mApplication->mSentLeaveGame == false)
	{
		//send quit game
        	ByteBuffer* byteBuffer = new ByteBuffer();
        	byteBuffer->WriteByte(mApplication->mGame->mMessageQuitGame);
        	mApplication->mNetwork->send(byteBuffer);
		LogString("send quit game");

                mApplication->mSentLeaveGame = true;
	}
	LogString("execute in ApplicationPlay mid");

	if (mApplication->mLeaveGame)
       	{
               	mApplication->mSentLeaveGame = false;
               	LogString("got mLeaveGame var change");
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
		LogString("execute in ApplicationPlay before processUpdate");
		if (mApplication->mGame)
		{	
               		mApplication->mGame->processUpdate();
		}
		LogString("execute in ApplicationPlay after processUpdate");
	}
	LogString("execute in ApplicationPlay");
}

void ApplicationPlay::exit()
{
	mApplication->mPlayingGame = false;
        mApplication->mLeaveGame = false;
        mApplication->mGame->remove();
	mApplication->mGame = NULL;
}
