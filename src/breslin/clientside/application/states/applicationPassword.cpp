//header
#include "applicationPassword.h"

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
ApplicationPassword::ApplicationPassword(ApplicationBreslin* applicationBreslin)
{
	mApplicationBreslin = applicationBreslin;
	//input
        mEditString = new EditString();
	mLoginSent = false;

}

ApplicationPassword::~ApplicationPassword()
{
}

void ApplicationPassword::enter()
{
	LogString("STATE: ApplicationPassword");
	createScreen();
	showScreen();
}

void ApplicationPassword::execute()
{
	//check for mFinal
	if (mLoginSent == false)
	{
		if (getEditString()->getIsFinal())
		{
			mApplicationBreslin->sendLogin();
		
			//set username string
			mPassword = getEditString()->getText();

			//change state to ???? state
			//mApplicationBreslin->mStateMachine->changeState(mApplicationBreslin->mApplicationPassword);
			//let's send login info then decide what state to go to....
	
			mLoginSent = true;	
		}
	}
	//check for input keys ..these will go to username and password for now
 	mLabelPasswordEdit->setCaption(getEditString()->getText());
}

void ApplicationPassword::exit()
{
 	getEditString()->clear();
	hideScreen();
}

//USERNAME
void ApplicationPassword::createScreen()
{
	if (!mLabelPassword)
	{
        	mLabelPassword = mApplicationBreslin->getTrayManager()->createLabel(OgreBites::TL_CENTER, "mLabelPassword", "Password:");
	}
	if (!mLabelPasswordEdit)
	{
        	mLabelPasswordEdit = mApplicationBreslin->getTrayManager()->createLabel(OgreBites::TL_CENTER, "mLabelPasswordEdit", "");
	}
	if (!mApplicationBreslin->mButtonExit)
	{
        	mApplicationBreslin->mButtonExit = mApplicationBreslin->getTrayManager()->createButton(OgreBites::TL_CENTER, "mButtonExit", "Exit Application");
	}
}

void ApplicationPassword::showScreen()
{
        mApplicationBreslin->getTrayManager()->moveWidgetToTray(mLabelPassword,OgreBites::TL_CENTER);
        mApplicationBreslin->getTrayManager()->moveWidgetToTray(mLabelPasswordEdit,OgreBites::TL_CENTER);

        mApplicationBreslin->getTrayManager()->moveWidgetToTray(mApplicationBreslin->mButtonExit,OgreBites::TL_CENTER);

        mLabelPassword->show();
        mLabelPasswordEdit->show();

        mApplicationBreslin->mButtonExit->show();

        mApplicationBreslin->getTrayManager()->showCursor();
}

void ApplicationPassword::hideScreen()
{
        mLabelPassword->hide();
        mLabelPasswordEdit->hide();

        mApplicationBreslin->mButtonExit->hide();
}

