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

//state machine
#include "../../statemachine/stateMachine.h"

//states
#include "states/gamePlayPartido.h"
#include "states/gamePlayPartidoBattle.h"


/***************************************
*			          CONSTRUCTORS
***************************************/
GamePartido::GamePartido(ApplicationBreslin* applicationBreslin) : Game(applicationBreslin)
{
   	mGamePlay = new GamePartidoPlay(this);
   	mGameBattle = new GameBattle(this);

	//change state
        mStateMachine->changeState(mGamePlay);

}

GamePartido::~GamePartido()
{
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

