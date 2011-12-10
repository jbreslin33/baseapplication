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
	
	
	
	if (mApplicationBreslin->mPlayingGame)
	{
		//game
		mApplicationBreslin->mGame->run();
	}
	else
	{
		mApplicationBreslin->shutdown();
			
			
		mApplicationBreslin->getSceneManager()->destroyAllEntities();
		delete mApplicationBreslin->mGame;

		mApplicationBreslin->showMainScreen();

		mApplicationBreslin->mStateMachine->changeState(mApplicationBreslin->mApplicationMain);
	}
}
void ApplicationPlay::exit()
{
}
