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
ApplicationLogin::ApplicationLogin(ApplicationBreslin* application)
{
	mApplication = application;
}

ApplicationLogin::~ApplicationLogin()
{

}

void ApplicationLogin::enter()
{
	mApplication->createLoginScreen();
	mApplication->showLoginScreen();
}

void ApplicationLogin::execute()
{
	if (mApplication->mLoggedIn == true)
	{
		mApplication->mStateMachine->changeState(mApplication->mApplicationMain);
	}

	if (mApplication->mButtonHit == mApplication->mButtonLogin)
	{
		mApplication->mButtonHit = NULL;
		if (mApplication->mStringUsername.size() > 0) 
		{
			mApplication->sendLogin();
		}
	}

	if (mApplication->mButtonHit == mApplication->mButtonExit)
	{
		mApplication->mStateMachine->changeState(NULL);
		mApplication->mStateMachine->setGlobalState(NULL);
		mApplication->mButtonHit = NULL;
		mApplication->shutdown();
		mApplication->mShutDown = true;
		delete mApplication;
	}
}

void ApplicationLogin::exit()
{
	mApplication->mStringUsername.clear();
	mApplication->mStringPassword.clear();

	mApplication->mLabelUsername->setCaption("Username");
	mApplication->mLabelPassword->setCaption("Password");

	mApplication->hideLoginScreen();
}

