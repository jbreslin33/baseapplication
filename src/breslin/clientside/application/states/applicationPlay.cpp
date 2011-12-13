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
}
void ApplicationPlay::execute()
{
	
	if (mApplicationBreslin->getKeyboard()->isKeyDown(OIS::KC_ESCAPE))
	{
		mApplicationBreslin->mPlayingGame = false;
		mApplicationBreslin->mStateMachine->changeState(mApplicationBreslin->mApplicationMain);
	}	
	else
	{
		//game
		mApplicationBreslin->mGame->processUpdate();
	}
	
}

void ApplicationPlay::exit()
{
	mApplicationBreslin->shutdown();
			
	mApplicationBreslin->getSceneManager()->destroyAllEntities();
	delete mApplicationBreslin->mGame;

	mApplicationBreslin->showMainScreen();
}
