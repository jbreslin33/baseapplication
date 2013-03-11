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
}

ApplicationUsername::~ApplicationUsername()
{
}

void ApplicationUsername::enter()
{
	LogString("STATE: ApplicationUsername");
	//mApplicationBreslin->showUsernameScreen();

	if (mApplicationBreslin->mLabelUsername)
	{

	}
	else
	{
		createUsernameScreen();
	}
	showUsernameScreen();
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
	hideUsernameScreen();
}
//USERNAME
void ApplicationUsername::createUsernameScreen()
{
        mApplicationBreslin->mLabelUsername     = mApplicationBreslin->mTrayMgr->createLabel(OgreBites::TL_CENTER, "mLabelUsername", "Username:");
        mApplicationBreslin->mLabelUsernameEdit = mApplicationBreslin->mTrayMgr->createLabel(OgreBites::TL_CENTER, "mLabelUsernameEdit", "");

        mApplicationBreslin->mButtonExit      = mApplicationBreslin->mTrayMgr->createButton(OgreBites::TL_CENTER, "mButtonExit", "Exit Application");
}

void ApplicationUsername::showUsernameScreen()
{
        mApplicationBreslin->mTrayMgr->moveWidgetToTray(mApplicationBreslin->mLabelUsername,OgreBites::TL_CENTER);
        mApplicationBreslin->mTrayMgr->moveWidgetToTray(mApplicationBreslin->mLabelUsernameEdit,OgreBites::TL_CENTER);

        mApplicationBreslin->mTrayMgr->moveWidgetToTray(mApplicationBreslin->mButtonExit,OgreBites::TL_CENTER);

        mApplicationBreslin->mLabelUsername->show();
        mApplicationBreslin->mLabelUsernameEdit->show();

        mApplicationBreslin->mButtonExit->show();

        mApplicationBreslin->mTrayMgr->showCursor();
}

void ApplicationUsername::hideUsernameScreen()
{
        mApplicationBreslin->mLabelUsername->hide();
        mApplicationBreslin->mLabelUsernameEdit->hide();

        mApplicationBreslin->mButtonExit->hide();
}

