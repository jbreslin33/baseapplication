//header
#include "applicationPlay.h"

//log
#include "../../tdreamsock/dreamSockLog.h"

//application
#include "../applicationBreslin.h"

//game
#include "../../game/game.h"

//state machine
#include "../../../statemachine/stateMachine.h"

/***************************************
*	CONSTRUCTORS
***************************************/
ApplicationPlay::ApplicationPlay(ApplicationBreslin* applicationBreslin)
{
	mApplicationBreslin = applicationBreslin;
}

ApplicationPlay::~ApplicationPlay()
{

}

void ApplicationPlay::enter()
{
	LogString("STATE: ApplicationPlay");
	LogString("create new Game");
        mApplicationBreslin->mGame = new Game(mApplicationBreslin);

}
void ApplicationPlay::execute()
{
	if (mApplicationBreslin->getKeyboard()->isKeyDown(OIS::KC_ESCAPE))
	{
		mApplicationBreslin->mPlayingGame = false;
		if (mApplicationBreslin->mLoggedIn)
		{
			mApplicationBreslin->mStateMachine->changeState(mApplicationBreslin->mApplicationMain);
		}
		else
		{
			mApplicationBreslin->mStateMachine->changeState(mApplicationBreslin->mApplicationLogin);
		}
	}
	else
	{
		//game
		mApplicationBreslin->mGame->processUpdate();
	}
}

void ApplicationPlay::exit()
{
	mApplicationBreslin->getSceneManager()->destroyAllEntities();
	mApplicationBreslin->mGame->quit();
	mApplicationBreslin->mGame = NULL;
}
