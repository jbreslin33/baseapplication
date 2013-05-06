//header
 #include "applicationPartido.h"

//log
#include "../tdreamsock/dreamSockLog.h"

//game
#include "../game/gamePartido.h"

//state machine
#include "../../statemachine/stateMachine.h"
#include "states/applicationGlobal.h"
#include "states/applicationLogin.h"
#include "states/applicationMainPartido.h"
#include "states/applicationInitialize.h"
#include "states/applicationPlay.h"

ApplicationPartido::ApplicationPartido(const char* serverIP, int serverPort) : ApplicationBreslin(serverIP,serverPort)
{

}

ApplicationPartido::~ApplicationPartido()
{
}

/*********************************
                        update
**********************************/
void ApplicationPartido::processUpdate()
{
	LogString("before mStateMachine->update");
        mStateMachine->update();
	LogString("after mStateMachine->update");

        if (mFake == true)
        {
                createLoginScreen();
                hideLoginScreen();

                mGame = new GamePartido(this);
                mGame->createStates();
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


void ApplicationPartido::createStates()
{
	LogString("CALLLED createStates in ApplicationPartido!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!");
        //state machine (Menus)
        mStateMachine = new StateMachine();

        mApplicationGlobal = new ApplicationGlobal(this);
        mApplicationInitialize = new ApplicationInitialize(this);
        mApplicationLogin   = new ApplicationLogin  (this);
        mApplicationMain   = new ApplicationMainPartido  (this);
        mApplicationPlay   = new ApplicationPlay(this);

        mStateMachine->setGlobalState (mApplicationGlobal);
        mStateMachine->changeState(mApplicationInitialize);
        mStateMachine->setPreviousState(mApplicationInitialize);
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


