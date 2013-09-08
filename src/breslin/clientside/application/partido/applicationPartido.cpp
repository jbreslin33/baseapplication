//header
 #include "applicationPartido.h"

//log
#include "../../tdreamsock/dreamSockLog.h"

//byteBuffer
#include "../../bytebuffer/byteBuffer.h"

//network
#include "../../network/network.h"

//game
#include "../../game/partido/gamePartido.h"

//move states
#include "states/applicationPartidoStates.h"

ApplicationPartido::ApplicationPartido(const char* serverIP, int serverPort) : ApplicationBreslin(serverIP,serverPort)
{
	mAnswerTime = 0;
	mGameCode = 2;
   
	//states
        mPartidoStateMachine =  new StateMachine<ApplicationPartido>(this);
        mPartidoStateMachine->setCurrentState      (INIT_PARTIDO_APPLICATION::Instance());
        mPartidoStateMachine->setPreviousState     (INIT_PARTIDO_APPLICATION::Instance());
        mPartidoStateMachine->setGlobalState       (GLOBAL_PARTIDO_APPLICATION::Instance());
}

ApplicationPartido::~ApplicationPartido()
{
}

/*********************************
        GAME
**********************************/
void ApplicationPartido::setGame(GamePartido* gamePartido)
{
        mGamePartido = gamePartido;
	ApplicationBreslin::setGame(gamePartido);
}
void ApplicationPartido::createGame()
{
        mGamePartido = new GamePartido(this);
	setGame(mGamePartido);
}

bool ApplicationPartido::frameRenderingQueued(const Ogre::FrameEvent& evt)
{
        bool ret = ApplicationBreslin::frameRenderingQueued(evt);
	unsigned int ms = mRenderTime * 1000;
	mAnswerTime = mAnswerTime + ms;
        return ret;
}

/*********************************
                        update
**********************************/
void ApplicationPartido::processUpdate()
{
	ApplicationBreslin::processUpdate();
        mPartidoStateMachine->update();
}

void  ApplicationPartido::createMainScreen()
{
	ApplicationBreslin::createMainScreen();
        if (!mButtonJoinGameB)
        {
                mButtonJoinGameB = mTrayMgr->createButton(OgreBites::TL_CENTER, "mButtonJoinGameB", "Join Game B");
        }
}

void  ApplicationPartido::showMainScreen()
{
	ApplicationBreslin::showMainScreen();
        mTrayMgr->moveWidgetToTray(mButtonJoinGameB,OgreBites::TL_CENTER);

        mButtonJoinGameB->show();
}

void  ApplicationPartido::hideMainScreen()
{
	ApplicationBreslin::hideMainScreen();
        mButtonJoinGameB->hide();

        mTrayMgr->removeWidgetFromTray(mButtonJoinGameB);
}

//battle
void  ApplicationPartido::createBattleScreen()
{
	LogString("b1");
        if (!mLabelQuestion)
        {
		LogString("b2");
		if (mTrayMgr)
		{
                	mLabelQuestion  = mTrayMgr->createLabel(OgreBites::TL_CENTER, "mLabelQuestion", "Question:");
		}
		else
		{
			LogString("NO mTrayMgr");
		}
        }
	LogString("b3");

        if (!mLabelAnswer)
        {
                mLabelAnswer  = mTrayMgr->createLabel(OgreBites::TL_CENTER, "mLabelAnswer", "Answer:");
        }
	LogString("b4");
}

void  ApplicationPartido::showBattleScreen()
{

        mTrayMgr->moveWidgetToTray(mLabelQuestion,OgreBites::TL_CENTER);
        mTrayMgr->moveWidgetToTray(mLabelAnswer,OgreBites::TL_CENTER);

        mLabelQuestion->show();
        mLabelAnswer->show();

        mTrayMgr->showCursor();

        mLabelFocus = mLabelAnswer;
}

void  ApplicationPartido::hideBattleScreen()
{
       	mLabelQuestion->hide();
        mLabelAnswer->hide();

        mTrayMgr->removeWidgetFromTray(mLabelQuestion);
        mTrayMgr->removeWidgetFromTray(mLabelAnswer);
}

//correctAnswer
void  ApplicationPartido::createCorrectAnswerScreen()
{
        if (!mLabelCorrectAnswer)
        {
                mLabelCorrectAnswer  = mTrayMgr->createLabel(OgreBites::TL_CENTER, "mLabelCorrectAnswer", "CorrectAnswer:");
        }
}

void  ApplicationPartido::showCorrectAnswerScreen()
{
        mTrayMgr->moveWidgetToTray(mLabelCorrectAnswer,OgreBites::TL_CENTER);
        mLabelCorrectAnswer->show();
        mTrayMgr->hideCursor();
        mLabelFocus = mLabelCorrectAnswer;
}

void  ApplicationPartido::hideCorrectAnswerScreen()
{
        mLabelCorrectAnswer->hide();
        mTrayMgr->removeWidgetFromTray(mLabelCorrectAnswer);
}


void ApplicationPartido::sendAnswer()
{
        ByteBuffer* byteBuffer = new ByteBuffer();
        byteBuffer->WriteByte(mMessageAnswerQuestion);
	
        byteBuffer->WriteShort(mAnswerTime);

        //get length of username
        int sizeOfAnswer = mStringAnswer.size();

        //write length of username
        byteBuffer->WriteByte(sizeOfAnswer);

        //loop thru answer string
        for (int i = 0; i < sizeOfAnswer; i++)
        {
                //write individual char of mStringAnswer
                byteBuffer->WriteByte(mStringAnswer.at(i));
        }

        //send it off to server
        mNetwork->send(byteBuffer);
}

