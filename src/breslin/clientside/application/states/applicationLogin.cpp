//header
#include "applicationLogin.h"

//log
#include "../../tdreamsock/dreamSockLog.h"

//application
#include "../applicationBreslin.h"

//state machine
#include "../../../statemachine/stateMachine.h"

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
	mApplicationBreslin->createLoginScreen();
	mApplicationBreslin->showLoginScreen();
}

void ApplicationLogin::execute()
{
	if (mApplicationBreslin->mLoggedIn == true)
	{
		mApplicationBreslin->mStateMachine->changeState(mApplicationBreslin->mApplicationMain);
	}

	if (mApplicationBreslin->mButtonHit == mApplicationBreslin->mButtonLogin)
	{
		mApplicationBreslin->mButtonHit = NULL;
		if (mApplicationBreslin->mStringUsername.size() > 0) 
		{
			mApplicationBreslin->sendLogin();
		}
	}

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
	mApplicationBreslin->mStringUsername.clear();
	mApplicationBreslin->mStringPassword.clear();

	mApplicationBreslin->mLabelUsername->setCaption("Username");
	mApplicationBreslin->mLabelPassword->setCaption("Password");

	mApplicationBreslin->hideLoginScreen();
}

