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
	//input
        mEditString = new EditString();

}

ApplicationUsername::~ApplicationUsername()
{
}

void ApplicationUsername::enter()
{
	LogString("STATE: ApplicationUsername");
	createScreen();
	showScreen();
}

void ApplicationUsername::execute()
{
	//check for mFinal
	if (getEditString()->getIsFinal())
	{
		LogString("mFinal = true");
		
		//set username string
		mUsername = getEditString()->getText();

		//change state to password state
		mApplicationBreslin->mStateMachine->changeState(mApplicationBreslin->mApplicationPassword);
	}

	//check for input keys ..these will go to username and password for now
 	mLabelUsernameEdit->setCaption(getEditString()->getText());
}

void ApplicationUsername::exit()
{
 	getEditString()->clear();
	hideScreen();
}

//USERNAME
void ApplicationUsername::createScreen()
{
	if (!mLabelUsername)
	{
        	mLabelUsername = mApplicationBreslin->getTrayManager()->createLabel(OgreBites::TL_CENTER, "mLabelUsername", "Username:");
	}
	if (!mLabelUsernameEdit)
	{
        	mLabelUsernameEdit = mApplicationBreslin->getTrayManager()->createLabel(OgreBites::TL_CENTER, "mLabelUsernameEdit", "");
	}
	if (!mApplicationBreslin->mButtonExit)
	{
        	mApplicationBreslin->mButtonExit = mApplicationBreslin->getTrayManager()->createButton(OgreBites::TL_CENTER, "mButtonExit", "Exit Application");
	}
}

void ApplicationUsername::showScreen()
{
        mApplicationBreslin->getTrayManager()->moveWidgetToTray(mLabelUsername,OgreBites::TL_CENTER);
        mApplicationBreslin->getTrayManager()->moveWidgetToTray(mLabelUsernameEdit,OgreBites::TL_CENTER);

        mApplicationBreslin->getTrayManager()->moveWidgetToTray(mApplicationBreslin->mButtonExit,OgreBites::TL_CENTER);

        mLabelUsername->show();
        mLabelUsernameEdit->show();

        mApplicationBreslin->mButtonExit->show();

        mApplicationBreslin->getTrayManager()->showCursor();
}

void ApplicationUsername::hideScreen()
{
        mLabelUsername->hide();
        mLabelUsernameEdit->hide();

        mApplicationBreslin->mButtonExit->hide();
}

