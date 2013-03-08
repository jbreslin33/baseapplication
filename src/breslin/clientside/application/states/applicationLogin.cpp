//header
#include "applicationLogin.h"


//log
#include "../../tdreamsock/dreamSockLog.h"

//application
#include "../applicationBreslin.h"

//game
#include "../../game/game.h"
#include "../../game/gameTag.h"

//state machine
#include "../../../statemachine/stateMachine.h"

/***************************************
*	CONSTRUCTORS
***************************************/
ApplicationLogin::ApplicationLogin(ApplicationBreslin* applicationBreslin)
{
	mApplicationBreslin = applicationBreslin;
}

ApplicationLogin::~ApplicationMain()
{

}

void ApplicationLogin::enter()
{
	LogString("STATE: ApplicationLogin");
	mApplicationBreslin->showLoginScreen();
}

void ApplicationLogin::execute()
{
	if (mApplicationBreslin->mButtonHit == mApplicationBreslin->mButtonLogin)
	{
/*
		mApplicationBreslin->mButtonHit = NULL;
		//is this the first c++ server knows of you? if so that is what i want? Or do I want a connection
		//right away? but without username? then we give username and a different connection.... 
		mApplicationBreslin->sendConnect();
		mApplicationBreslin->mGame = new Game(mApplicationBreslin);

		mApplicationBreslin->hideLoginScreen();

		mApplicationBreslin->mStateMachine->changeState(mApplicationBreslin->mApplicationPlay);
*/
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

void ApplicationMain::exit()
{

}
