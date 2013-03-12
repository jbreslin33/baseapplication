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
	if (mApplicationBreslin->mEditString->getIsFinal())
	{
		LogString("mFinal = true");
		
		//set username string
		mPassword = mApplicationBreslin->getEditString()->getText();

		//change state to password state
		mApplicationBreslin->mStateMachine->changeState(mApplicationBreslin->mApplicationPassword);
	}

	//check for input keys ..these will go to username and password for now
 	mLabelPasswordEdit->setCaption(mApplicationBreslin->getEditString()->getText());
}

void ApplicationPassword::exit()
{
 	mApplicationBreslin->mEditString->clear();
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

