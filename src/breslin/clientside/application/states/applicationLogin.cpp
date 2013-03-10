//header
#include "applicationLogin.h"

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
ApplicationLogin::ApplicationLogin(ApplicationBreslin* applicationBreslin)
{
	mApplicationBreslin = applicationBreslin;
}

ApplicationLogin::~ApplicationLogin()
{
}

void ApplicationLogin::enter()
{
	LogString("STATE: ApplicationLogin");
	//mApplicationBreslin->showLoginScreen();
}

void ApplicationLogin::execute()
{
	//check for input keys ..these will go to username and password for now
 	mApplicationBreslin->mLabelLoginEdit->setCaption(mApplicationBreslin->mEditString->getText());

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

void ApplicationLogin::exit()
{
 	mApplicationBreslin->mEditString->clear();
}
