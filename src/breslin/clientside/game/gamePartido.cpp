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
#include "states/gamePlayPartidoShowCorrectAnswer.h"

/***************************************
*			          CONSTRUCTORS
***************************************/
GamePartido::GamePartido(ApplicationPartido* applicationPartido) : Game(applicationPartido)
{
	mApplicationPartido = applicationPartido;

	//battle
	mBattleStart = false;
	mBattleEnd   = false;

	//correctAnswer
	mCorrectAnswerStart = false;
	mCorrectAnswer = false;
	mCorrectAnswerEnd = false;
}

GamePartido::~GamePartido()
{
}

void GamePartido::createStates()
{
   	mGamePlay              = new GamePlayPartido(this);
   	mGamePlayPartidoBattle = new GamePlayPartidoBattle(this);
   	mGamePlayPartidoShowCorrectAnswer = new GamePlayPartidoShowCorrectAnswer(this);
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
                
		case mMessageCorrectAnswerStart:
                        correctAnswer(byteBuffer);
                        break;
		
		case mMessageCorrectAnswerEnd:
			mCorrectAnswerEnd = true;
                        break;
        }
}

void GamePartido::correctAnswer(ByteBuffer* byteBuffer)
{
	mCorrectAnswerStart = true;

        mApplicationPartido->mStringCorrectAnswer.clear();

        int length = byteBuffer->ReadByte();
        for (int i = 0; i < length; i++)
        {
                char c =  byteBuffer->ReadByte();
                mApplicationPartido->mStringCorrectAnswer.append(1,c);
        }
        if (mApplicationPartido->mLabelCorrectAnswer && mApplicationPartido->mStringCorrectAnswer.size() > 0)
        {
                mApplicationPartido->mLabelCorrectAnswer->setCaption(mApplicationPartido->mStringCorrectAnswer);
        }
        else
        {
                LogString("no label or no string");
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
	if (mApplicationPartido->mLabelQuestion && mApplicationPartido->mStringQuestion.size() > 0)
	{
		mApplicationPartido->mLabelQuestion->setCaption(mApplicationPartido->mStringQuestion);
	}
	else
	{
		LogString("no label or no string");
	}
	
	//reset mAnswerTime	
	mApplicationPartido->mAnswerTime = 0; 
}

