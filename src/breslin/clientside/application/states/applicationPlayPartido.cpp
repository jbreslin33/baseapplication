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
		if (mApplicationPartido->mGamePartido->mStateMachine->getCurrentState() == mApplicationPartido->mGamePartido->mGamePartidoPlayPartidoBattle)
		{
 			mApplicationPartido->mGamePartido->mKeyArray[27] = false;

                	//send quit game
                	ByteBuffer* byteBuffer = new ByteBuffer();
                	byteBuffer->WriteByte(mApplicationPartido->mGamePartido->mMessageLeaveGame);
                	mApplicationPartido->mGamePartido->mNetwork->send(byteBuffer);
                	mApplicationPartido->mGamePartido->mSentLeaveGame = true;
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
                if (mApplicationPartido->mGamePartido)
                {
                        mApplicationPartido->mGamePartido->processUpdate();
                }
        }

//	ApplicationPlay::execute();
}

void ApplicationPlayPartido::exit()
{
 	mApplicationPartido->mPlayingGame = false;
        mApplicationPartido->mLeaveGame = false;
        if (mApplicationPartido->mGamePartido)
        {
                mApplicationPartido->mGamePartido->remove();
                mApplicationPartido->mGamePartido = NULL;
        }
//	ApplicationPlay::exit();
}
