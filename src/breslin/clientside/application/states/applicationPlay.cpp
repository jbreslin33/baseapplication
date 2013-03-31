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
        mApplicationBreslin->mGame = new Game(mApplicationBreslin);
        mApplicationBreslin->mPlayingGame = true;
        mApplicationBreslin->mSentLeaveGame = false;
}
void ApplicationPlay::execute()
{
	if (mApplicationBreslin->getKeyboard()->isKeyDown(OIS::KC_ESCAPE) && mApplicationBreslin->mSentLeaveGame == false)
	{
		//send quit game
        	ByteBuffer* byteBuffer = new ByteBuffer();
        	byteBuffer->WriteByte(mApplicationBreslin->mGame->mMessageQuitGame);
        	mApplicationBreslin->mNetwork->send(byteBuffer);
		LogString("send quit game");

                mApplicationBreslin->mSentLeaveGame = true;
	}

	if (mApplicationBreslin->mLeaveGame)
       	{
               	mApplicationBreslin->mSentLeaveGame = false;
               	LogString("got mLeaveGame var change");
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
               	mApplicationBreslin->mGame->processUpdate();
	}
}

void ApplicationPlay::exit()
{
	mApplicationBreslin->mPlayingGame = false;
        mApplicationBreslin->mLeaveGame = false;
        mApplicationBreslin->mGame->remove();
	mApplicationBreslin->mGame = NULL;
}
