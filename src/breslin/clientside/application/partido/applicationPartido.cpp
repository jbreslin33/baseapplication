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

GamePartido* ApplicationPartido::getGame()
{
        return mGamePartido;
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
        mStateMachine->update();

        if (mFake == true)
        {
		//battle screen init...
		createBattleScreen();
		showBattleScreen();
		hideBattleScreen();
		
		//correctAnswer screen init...
		createCorrectAnswerScreen();
		showCorrectAnswerScreen();
		hideCorrectAnswerScreen();

		//login init
                createLoginScreen();
                hideLoginScreen();

                setGame(new GamePartido(this));
                mStateMachine->changeState(mApplicationPlay);

                //sneak an update in
                mStateMachine->update();

                //fake esc from game
                mPlayingGame = false;
                mStateMachine->changeState(mApplicationLogin);

		mFake = false;
        }

        //did you sendConnect if not do so
        if (!mConnectSent)
        {
                mConnectSent = true;
                sendConnect();
        }
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
        if (!mLabelQuestion)
        {
                mLabelQuestion  = mTrayMgr->createLabel(OgreBites::TL_CENTER, "mLabelQuestion", "Question:");
        }

        if (!mLabelAnswer)
        {
                mLabelAnswer  = mTrayMgr->createLabel(OgreBites::TL_CENTER, "mLabelAnswer", "Answer:");
        }
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

