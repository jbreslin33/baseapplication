//header
 #include "applicationPartido.h"

//log
#include "../tdreamsock/dreamSockLog.h"

//byteBuffer
#include "../bytebuffer/byteBuffer.h"

//network
#include "../network/network.h"

//game
#include "../game/gamePartido.h"

//state machine
#include "../../statemachine/stateMachine.h"
#include "states/applicationGlobal.h"
#include "states/applicationLogin.h"
#include "states/applicationMainPartido.h"
#include "states/applicationInitialize.h"
#include "states/applicationPlayPartido.h"

ApplicationPartido::ApplicationPartido(const char* serverIP, int serverPort) : ApplicationBreslin(serverIP,serverPort)
{
	LogString("ApplicationPartido::ApplicationPartido");
}

ApplicationPartido::~ApplicationPartido()
{
}

void ApplicationPartido::createStates()
{
	LogString("ApplicationPartido::createStates");
        mApplicationGlobal     = new ApplicationGlobal(this);
        mApplicationInitialize = new ApplicationInitialize(this);
        mApplicationLogin      = new ApplicationLogin  (this);
        mApplicationMain       = new ApplicationMainPartido  (this);
        mApplicationPlay       = new ApplicationPlayPartido(this);
}

void ApplicationPartido::setStates()
{
	LogString("ApplicationPartido::setStates");
        mStateMachine->setGlobalState (mApplicationGlobal);
        mStateMachine->changeState(mApplicationInitialize);
        mStateMachine->setPreviousState(mApplicationInitialize);
}

/*********************************
                        update
**********************************/
void ApplicationPartido::processUpdate()
{
        mStateMachine->update();

        if (mFake == true)
        {
                createLoginScreen();
                hideLoginScreen();

                mGame = new GamePartido(this);
		mGame->createStates();
		mGame->setStates();
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
        LogString("ApplicationPartido::createBattleScreen");

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
	if (mFake)
	{
		return;	
	}
       	mLabelQuestion->hide();
        mLabelAnswer->hide();

        mTrayMgr->removeWidgetFromTray(mLabelQuestion);
        mTrayMgr->removeWidgetFromTray(mLabelAnswer);
}

bool ApplicationPartido::keyPressed( const OIS::KeyEvent &arg )
{
	ApplicationBreslin::keyPressed(arg);

	if (!mFake)
	{
		if (mLabelFocus == mLabelAnswer)
		{
	     		int numeric = arg.text;
                        char ascii = (char)numeric;

                        if (numeric == 8) //backspace
                        {
                                int size = mStringAnswer.size();
                                if (size > 0)
                                {
                                        mStringAnswer.resize(size - 1);
                                }
                                mLabelAnswer->setCaption(mStringAnswer);
                        }

                        if (numeric == 13) //carriage return  or enter 
                        {
				LogString("enter!!!");
				sendAnswer();
                                mStringAnswer.clear();
                                mLabelAnswer->setCaption(mStringAnswer);
                        }

                        if (numeric > 47 && numeric < 123) //letters and valid symbols for username and password
                        {
                                mStringAnswer.append(1,ascii);
                                mLabelAnswer->setCaption(mStringAnswer);
                        }
			
		}	
	}
}

void ApplicationPartido::sendAnswer()
{
        ByteBuffer* byteBuffer = new ByteBuffer();
        byteBuffer->WriteByte(mMessageAnswerQuestion);
	int mAnswerTime = 120;
        byteBuffer->WriteByte(mAnswerTime);

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
	LogString("sendAnswer");
        mNetwork->send(byteBuffer);
}

