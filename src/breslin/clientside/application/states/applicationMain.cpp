//header
#include "applicationMain.h"


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
	mApplicationBreslin->showMainScreen();
}

void ApplicationMain::execute()
{
	/**********LOGIN*************/
	if (mApplicationBreslin->mButtonHit == mApplicationBreslin->mButtonLogin)
	{
		mApplicationBreslin->mButtonHit = NULL;

		mApplicationBreslin->sendLogin();
	}


	/************JOIN GAME**********/

	if (mApplicationBreslin->mButtonHit == mApplicationBreslin->mButtonJoinGame)
	{
		mApplicationBreslin->mButtonHit = NULL;

		mApplicationBreslin->sendJoinGame();
		
		mApplicationBreslin->mStateMachine->changeState(mApplicationBreslin->mApplicationPlay);
	}

	/************JOIN GAME**********/
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
