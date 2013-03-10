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
	//mApplicationBreslin->processInput();
 	mApplicationBreslin->mLabelUsername->setCaption(mApplicationBreslin->mEditString->getText());
 //mLabelUsername->setCaption(mEditString->getText());

	if (mApplicationBreslin->mButtonHit == mApplicationBreslin->mButtonLogin)
	{
		LogString("login button hit");
		mApplicationBreslin->mButtonHit = NULL;
	}
	
	if (mApplicationBreslin->mButtonHit == mApplicationBreslin->mButtonSignup)
	{
		mApplicationBreslin->mButtonHit = NULL;
		LogString("signup button hit");
	
	}

	if (mApplicationBreslin->mButtonHit == mApplicationBreslin->mButtonPractice)
	{
		mApplicationBreslin->mButtonHit = NULL;
		LogString("practice button hit");
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
}
