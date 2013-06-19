//header
#include "applicationPlayPartido.h"

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
ApplicationPlayPartido::ApplicationPlayPartido(ApplicationPartido* applicationPartido) : ApplicationPlay(applicationPartido)
{
	mApplicationPartido = applicationPartido;
}

ApplicationPlayPartido::~ApplicationPlayPartido()
{

}

void ApplicationPlayPartido::enter()
{
	mApplicationPartido->mPlayingGame = true;
        mApplicationPartido->mSentLeaveGame = false;
	//ApplicationPlay::enter();

}

void ApplicationPlayPartido::execute()
{
  //check for logout as well....
        if (this->mApplicationPartido->mLoggedIn == false )
        {
                this->mApplicationPartido->mStateMachine->changeState(this->mApplicationPartido->mApplicationLogin);
        }

        if (mApplicationPartido->mKeyArray[27]) //esc
        {
                mApplicationPartido->mKeyArray[27] = false;

                //send quit game
                ByteBuffer* byteBuffer = new ByteBuffer();
                byteBuffer->WriteByte(mApplicationPartido->mMessageLeaveGame);
                mApplicationPartido->mNetwork->send(byteBuffer);
                mApplicationPartido->mSentLeaveGame = true;

		//check to see if in battle....	
/*
		if (mApplicationPartido->mGame->mStateMachine->getCurrentState() == mApplicationPartido->mGame->mGamePlayPartidoBattle)
		{
 			mApplicationPartido->mGame->mKeyArray[27] = false;

                	//send quit game
                	ByteBuffer* byteBuffer = new ByteBuffer();
                	byteBuffer->WriteByte(mApplicationPartido->mGame->mMessageLeaveGame);
                	mApplicationPartido->mGame->mNetwork->send(byteBuffer);
                	mApplicationPartido->mGame->mSentLeaveGame = true;
		}
*/
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
                if (mApplicationPartido->mGame)
                {
                        mApplicationPartido->mGame->processUpdate();
                }
        }

//	ApplicationPlay::execute();
}

void ApplicationPlayPartido::exit()
{
 	mApplicationPartido->mPlayingGame = false;
        mApplicationPartido->mLeaveGame = false;
        if (mApplicationPartido->mGame)
        {
                mApplicationPartido->mGame->remove();
                mApplicationPartido->mGame = NULL;
        }
//	ApplicationPlay::exit();
}
