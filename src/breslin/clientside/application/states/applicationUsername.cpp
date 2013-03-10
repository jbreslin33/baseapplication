//header
#include "applicationUsername.h"

//log
#include "../../tdreamsock/dreamSockLog.h"

//application
#include "../applicationBreslin.h"

//state machine
#include "../../../statemachine/stateMachine.h"

//input
#include "../../io/editString.h"

/***************************************
*	CONSTRUCTORS
***************************************/
ApplicationUsername::ApplicationUsername(ApplicationBreslin* applicationBreslin)
{
	mApplicationBreslin = applicationBreslin;
	mTrayMgr = new OgreBites::SdkTrayManager("InterfaceName", mApplicationBreslin->mWindow, mApplicationBreslin->mMouse, mApplicationBreslin);

}

ApplicationUsername::~ApplicationUsername()
{
}

void ApplicationUsername::enter()
{
	LogString("STATE: ApplicationUsername");
	//mApplicationBreslin->showUsernameScreen();
}

void ApplicationUsername::execute()
{
	//check for input keys ..these will go to username and password for now
 	mApplicationBreslin->mLabelUsernameEdit->setCaption(mApplicationBreslin->mEditString->getText());

	if (mApplicationBreslin->mButtonHit == mApplicationBreslin->mButtonExit)
	{
		mApplicationBreslin->mStateMachine->changeState(NULL);
		mApplicationBreslin->mStateMachine->setGlobalState(NULL);

		mApplicationBreslin->mButtonHit = NULL;

		mApplicationBreslin->shutdown();

		mApplicationBreslin->mShutDown = true;

		delete mApplicationBreslin;
	}
}

void ApplicationUsername::exit()
{
 	mApplicationBreslin->mEditString->clear();
}

//USERNAME
void ApplicationUsername::createUsernameScreen()
{
        mLabelUsername     = mTrayMgr->createLabel(OgreBites::TL_CENTER, "mLabelUsername", "Username:");
        mLabelUsernameEdit = mTrayMgr->createLabel(OgreBites::TL_CENTER, "mLabelUsernameEdit", "");

        mApplicationBreslin->mButtonExit      = mTrayMgr->createButton(OgreBites::TL_CENTER, "mButtonExit", "Exit Application");
}

void ApplicationUsername::showUsernameScreen()
{
        mTrayMgr->moveWidgetToTray(mLabelUsername,OgreBites::TL_CENTER);
        mTrayMgr->moveWidgetToTray(mLabelUsernameEdit,OgreBites::TL_CENTER);

        mTrayMgr->moveWidgetToTray(mButtonExit,OgreBites::TL_CENTER);

        mLabelUsername->show();
        mLabelUsernameEdit->show();

        mButtonExit->show();

        mTrayMgr->showCursor();
}

void ApplicationUsername::hideUsernameScreen()
{
        mLabelUsername->hide();
        mLabelUsernameEdit->hide();

        mApplicationBreslin->mButtonExit->hide();
}

