//header
#include "applicationGameReset.h"

//log
#include "../../tdreamsock/dreamSockLog.h"

//application
#include "../applicationPartido.h"

//game
#include "../../game/gamePartido.h"

//state machine
#include "../../../statemachine/stateMachine.h"

//byteBuffer
#include "../../bytebuffer/byteBuffer.h"

//byteBuffer
#include "../../network/network.h"

/***************************************
*	CONSTRUCTORS
***************************************/
ApplicationGameReset::ApplicationGameReset(ApplicationBreslin* applicationBreslin) 
{
	mApplicationBreslin = applicationBreslin;
}

ApplicationGameReset::~ApplicationGameReset()
{

}

void ApplicationGameReset::enter()
{
}

void ApplicationGameReset::execute()
{
  //check for logout as well....
/*
        if (this->mApplicationPartido->mLoggedIn == false )
        {
                this->mApplicationPartido->mStateMachine->changeState(this->mApplicationPartido->mApplicationLogin);
        }

        if (mApplicationPartido->mKeyArray[27]) //esc
        {
		//check to see if in battle....	
		if (mApplicationPartido->getGame()->mStateMachine->getCurrentState() == mApplicationPartido->getGame()->mGamePlayPartidoBattle)
		{
			mApplicationPartido->mAnswerTime = 2001;
			mApplicationPartido->mStringAnswer = "esc";
			LogString("sendAnswer via esc");
			mApplicationPartido->sendAnswer();
		}
		else
		{
			mApplicationPartido->mKeyArray[27] = false;
                	ByteBuffer* byteBuffer = new ByteBuffer();
                	byteBuffer->WriteByte(mApplicationPartido->mMessageLeaveGame);
                	mApplicationPartido->mNetwork->send(byteBuffer);
                	mApplicationPartido->mSentLeaveGame = true;
       		} 
	}

        if (mApplicationPartido->mLeaveGame)
        {
                LogString("mLeaveGame true");
                mApplicationPartido->mSentLeaveGame = false;
                if (mApplicationPartido->mLoggedIn)
                {
                        mApplicationPartido->mStateMachine->changeState(mApplicationPartido->mApplicationMain);
                }
                else
                {
                        mApplicationPartido->mStateMachine->changeState(mApplicationPartido->mApplicationLogin);
                }
        }
        else
        {
                //game
                if (mApplicationPartido->getGame())
                {
                        mApplicationPartido->getGame()->processUpdate();
                }
        }
*/
}

void ApplicationGameReset::exit()
{
/*
 	mApplicationPartido->mPlayingGame = false;
        mApplicationPartido->mLeaveGame = false;
        if (mApplicationPartido->getGame())
        {
                mApplicationPartido->getGame()->remove();
                mApplicationPartido->setGame(NULL);
        }
*/
}
