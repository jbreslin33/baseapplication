//header
#include "gamePartido.h"

//log
#include "../../tdreamsock/dreamSockLog.h"

//ObjectTitle
#include "../../billboard/objectTitle.h"

//byteBuffer
#include "../../bytebuffer/byteBuffer.h"

//shape
#include "../../shape/shape.h"

//application
#include "../../application/partido/applicationPartido.h"

//states
#include "states/gamePartidoStates.h"

/***************************************
*			          CONSTRUCTORS
***************************************/
GamePartido::GamePartido(ApplicationPartido* applicationPartido) : Game(applicationPartido)
{
	mApplicationPartido = applicationPartido;

/*
  //reset battle vars
        mBattleStart = false;
        mCorrectAnswerStart = false;
        mApplicationPartido->mGameReset = false;

        //reset correctAnswer vars
        mCorrectAnswerStart = false;
        mCorrectAnswer      = false;
        mCorrectAnswerEnd   = false;

        //answer time
        mApplicationPartido->mAnswerTime = 0;

*/


	//battle
	mBattleStart = false;
	mFirstTimeExecute = true;

	//correctAnswer
	mCorrectAnswerStart = false;
	mCorrectAnswerEnd = false;

	//states
        mPartidoStateMachine =  new StateMachine<GamePartido>(this);
        mPartidoStateMachine->setCurrentState      (PLAY_PARTIDO_GAME::Instance());
        mPartidoStateMachine->setPreviousState     (PLAY_PARTIDO_GAME::Instance());
        mPartidoStateMachine->setGlobalState       (NULL);

	//states
        mBattleStateMachine =  new StateMachine<GamePartido>(this);
        mBattleStateMachine->setCurrentState      (BATTLE_OFF::Instance());
        mBattleStateMachine->setPreviousState     (BATTLE_OFF::Instance());
        mBattleStateMachine->setGlobalState       (NULL);

	mApplicationPartido->createBattleScreen();
        mApplicationPartido->hideBattleScreen();
        mApplicationPartido->createCorrectAnswerScreen();
        mApplicationPartido->hideCorrectAnswerScreen();
}

GamePartido::~GamePartido()
{
}

void GamePartido::processUpdate()
{
	Game::processUpdate();
        mPartidoStateMachine->update();
        mBattleStateMachine->update();
}

void GamePartido::processMoveControls()
{
	if (mBattleStateMachine->currentState() != BATTLE_OFF::Instance())
	{
		//we are in battle			
	}	
	else
	{
		//not in battle let player move
		Game::processMoveControls();
	}
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
 			mBattleStateMachine->changeState(BATTLE_OFF::Instance());                        
			break;
                
		case mMessageCorrectAnswerStart:
			mCorrectAnswerStart = true;
                        correctAnswer(byteBuffer);
                        break;
		
		case mMessageCorrectAnswerEnd:
			mCorrectAnswerEnd = true;
                        break;
        }
}

void GamePartido::correctAnswer(ByteBuffer* byteBuffer)
{
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

	const char * q = mApplicationPartido->mStringQuestion.c_str();
        //LogString("q:%s",q);

	if (!mApplicationPartido->mLabelQuestion)
	{
		LogString("GamePartido::askQuestion : no mLabelQuestion exists yet.");
	}
	if (mApplicationPartido->mStringQuestion.size() < 1)
	{
		LogString("GamePartido::askQuestion : mStringQuestion less than 1 in size.");
	}
	if (mApplicationPartido->mLabelQuestion && mApplicationPartido->mStringQuestion.size() > 0)
	{
		mApplicationPartido->mLabelQuestion->setCaption(mApplicationPartido->mStringQuestion);
		//LogString("just setCaption on mLabelQuestion");
	}
	else
	{
		LogString("GamePartido::askQuestion : no label or no string");
	}
	
	//reset mAnswerTime	
	mApplicationPartido->mAnswerTime = 0; 
}

void GamePartido::reset()
{
	Game::reset();
      	
	//hide screens 
	mApplicationPartido->hideBattleScreen();
	mApplicationPartido->hideCorrectAnswerScreen();
 	
	//reset text boxes for battle ...actually let's not
        mApplicationPartido->mStringAnswer.clear();
        mApplicationPartido->mLabelQuestion->setCaption("");
        mApplicationPartido->mLabelAnswer->setCaption("");

	//reset text boxes for showCorrectAnswer ...actually let's not
        mApplicationPartido->mLabelCorrectAnswer->setCaption("");
        mApplicationPartido->mStringCorrectAnswer.clear();

	//reset battle vars
        mBattleStart = false;
        mCorrectAnswerStart = false;
        mApplicationPartido->mGameReset = false;

	//reset correctAnswer vars
        mCorrectAnswerStart = false;
        mCorrectAnswerEnd   = false;

	//answer time
        mApplicationPartido->mAnswerTime = 0;
}

