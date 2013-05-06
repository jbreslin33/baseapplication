//header
#include "applicationMain.h"


//log
#include "../../tdreamsock/dreamSockLog.h"

//application
#include "../applicationBreslin.h"

//game
#include "../../game/gamePartido.h"

//state machine
#include "../../../statemachine/stateMachine.h"

/***************************************
*	CONSTRUCTORS
***************************************/
ApplicationMain::ApplicationMain(ApplicationBreslin* application)
{
	mApplication = application;
}

ApplicationMain::~ApplicationMain()
{

}

void ApplicationMain::enter()
{
	LogString("STATE: ApplicationGlobal");
	mApplication->createMainScreen();
	mApplication->showMainScreen();
}

void ApplicationMain::execute()
{
	if (mApplication->mButtonHit == mApplication->mButtonJoinGameA)
	{
		mApplication->mButtonHit = NULL;
 		mApplication->mGame = new Game(mApplication);
		mApplication->mGame->createStates();
		mApplication->sendJoinGame(1);
		mApplication->mStateMachine->changeState(mApplication->mApplicationPlay);
	}

	if (mApplication->mButtonHit == mApplication->mButtonLogout)
	{
		mApplication->mButtonHit = NULL;
		mApplication->sendLogout();
	}
	
	if (mApplication->mLoggedIn == false)
	{
		mApplication->mStateMachine->changeState(mApplication->mApplicationLogin);
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

void ApplicationMain::exit()
{
	mApplication->hideMainScreen();
}

