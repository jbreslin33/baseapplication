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
	//mApplicationBreslin->showPasswordScreen();
}

void ApplicationPassword::execute()
{
	//check for input keys ..these will go to username and password for now
 	mApplicationBreslin->mLabelPasswordEdit->setCaption(mApplicationBreslin->mEditString->getText());

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

void ApplicationPassword::exit()
{
 	mApplicationBreslin->mEditString->clear();
}
