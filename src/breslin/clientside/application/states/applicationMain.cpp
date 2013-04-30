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
ApplicationMain::ApplicationMain(ApplicationBreslin* applicationBreslin)
{
	mApplicationBreslin = applicationBreslin;
}

ApplicationMain::~ApplicationMain()
{

}

void ApplicationMain::enter()
{
	LogString("STATE: ApplicationGlobal");
	mApplicationBreslin->createMainScreen();
	mApplicationBreslin->showMainScreen();
}

void ApplicationMain::execute()
{
	if (mApplicationBreslin->mButtonHit == mApplicationBreslin->mButtonJoinGameA)
	{
		mApplicationBreslin->mButtonHit = NULL;
 		mApplicationBreslin->mGame = new Game(mApplicationBreslin);
		mApplicationBreslin->sendJoinGame(1);
		mApplicationBreslin->mStateMachine->changeState(mApplicationBreslin->mApplicationPlay);
	}

	if (mApplicationBreslin->mButtonHit == mApplicationBreslin->mButtonJoinGameB)
	{
		mApplicationBreslin->mButtonHit = NULL;
 		mApplicationBreslin->mGame = new GamePartido(mApplicationBreslin);
		mApplicationBreslin->sendJoinGame(2);
		mApplicationBreslin->mStateMachine->changeState(mApplicationBreslin->mApplicationPlay);
	}

	if (mApplicationBreslin->mButtonHit == mApplicationBreslin->mButtonLogout)
	{
		mApplicationBreslin->mButtonHit = NULL;
		mApplicationBreslin->sendLogout();
	}
	
	if (mApplicationBreslin->mLoggedIn == false)
	{
		mApplicationBreslin->mStateMachine->changeState(mApplicationBreslin->mApplicationLogin);
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
	mApplicationBreslin->hideMainScreen();
}

