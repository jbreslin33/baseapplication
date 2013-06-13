//header
#include "gamePartido.h"

//log
#include "../tdreamsock/dreamSockLog.h"

//ObjectTitle
#include "../billboard/objectTitle.h"

//byteBuffer
#include "../bytebuffer/byteBuffer.h"

//shape
#include "../shape/shape.h"

//application
#include "../application/applicationPartido.h"

//state machine
#include "../../statemachine/stateMachine.h"
#include "states/gamePlay.h"
#include "states/gamePlayPartido.h"
#include "states/gamePlayPartidoBattle.h"

/***************************************
*			          CONSTRUCTORS
***************************************/
GamePartido::GamePartido(ApplicationPartido* applicationPartido) : Game(applicationPartido)
{
	mApplicationPartido = applicationPartido;
	mBattleStart = false;
	mBattleEnd   = false;
}

GamePartido::~GamePartido()
{
}

void GamePartido::createStates()
{
   	mGamePlay              = new GamePlayPartido(this);
   	mGamePlayPartidoBattle = new GamePlayPartidoBattle(this);
}

void GamePartido::setStates()
{
        mStateMachine->setGlobalState(NULL);
        mStateMachine->changeState(mGamePlay);
}


void GamePartido::checkByteBuffer(ByteBuffer* byteBuffer)
{
	Game::checkByteBuffer(byteBuffer);

        byteBuffer->BeginReading();

        int type = byteBuffer->ReadByte();
       
	switch(type)
        {
                case mMessageAskQuestion:
                        askQuestion(byteBuffer);
                        break;

                case mMessageBattleStart:
			mBattleStart = true;
                        break;

                case mMessageBattleEnd:
			mBattleEnd = true;
                        break;
        }
}

void GamePartido::askQuestion(ByteBuffer* byteBuffer)
{
	mApplicationPartido->mStringQuestion.clear();
        int length = byteBuffer->ReadByte();
        for (int i = 0; i < length; i++)
        {
        	char c =  byteBuffer->ReadByte();
                mApplicationPartido->mStringQuestion.append(1,c);
        }
	if (mApplicationPartido->mLabelQuestion)
	{
		mApplicationPartido->mLabelQuestion->setCaption(mApplicationPartido->mStringQuestion);
	}
	else
	{
		LogString("no label");
	}
	
	//reset mAnswerTime	
	mApplicationPartido->mAnswerTime = 0; 
}

