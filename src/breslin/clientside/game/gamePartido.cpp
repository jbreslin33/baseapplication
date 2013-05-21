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
#include "states/gameGlobal.h"
#include "states/gameInitialize.h"
#include "states/gamePlay.h"
#include "states/gamePause.h"
#include "states/gamePlayPartido.h"
#include "states/gamePlayPartidoBattle.h"

/***************************************
*			          CONSTRUCTORS
***************************************/
GamePartido::GamePartido(ApplicationPartido* applicationPartido) : Game(applicationPartido)
{
	LogString("GamePartio::GamePartido");
	mApplication = applicationPartido;
	mBattleStart = false;
	mBattleEnd   = false;
}

GamePartido::~GamePartido()
{
}

void GamePartido::createStates()
{
        mGameGlobal            = new GameGlobal(this);
        mGameInitialize        = new GameInitialize(this);
   	mGamePlay              = new GamePlayPartido(this);
        mGamePause             = new GamePause(this);
   	mGamePlayPartidoBattle = new GamePlayPartidoBattle(this);
}

void GamePartido::setStates()
{
        mStateMachine->setGlobalState(mGameGlobal);
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
                        battleStart(byteBuffer);
                        break;

                case mMessageBattleEnd:
                        battleEnd(byteBuffer);
                        break;
        }
}

void GamePartido::battleStart(ByteBuffer* byteBuffer)
{
	mBattleStart = true;
	LogString("battleStart");
}

void GamePartido::battleEnd(ByteBuffer* byteBuffer)
{
	mBattleEnd = true;
	LogString("battleEnd");
}

void GamePartido::askQuestion(ByteBuffer* byteBuffer)
{
	LogString("askQuestion...");
	std::string question;
        int length = byteBuffer->ReadByte();
        for (int i = 0; i < length; i++)
        {
        	char c =  byteBuffer->ReadByte();
                question.append(1,c);
        }

	for(int i = 0; i < mShapeVector->size(); i++)
	{	
		if (mShapeVector->at(i)->mLocal == 1)
		{
			mShapeVector->at(i)->clearTitle();
			mShapeVector->at(i)->appendToTitle(question);
		}
	}
}

