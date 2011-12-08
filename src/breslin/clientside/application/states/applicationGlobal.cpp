//header
#include "applicationGlobal.h"

//log
#include "../../tdreamsock/dreamSockLog.h"

//application
#include "../applicationBreslin.h"

//game
#include "../../game/game.h"

/***************************************
*	CONSTRUCTORS		          
***************************************/
ApplicationGlobal::ApplicationGlobal(ApplicationBreslin* applicationBreslin)
{
	mApplicationBreslin = applicationBreslin;
}

ApplicationGlobal::~ApplicationGlobal()
{

}

void ApplicationGlobal::enter()
{

}
void ApplicationGlobal::execute()
{
	//mApplicationBreslin->applicationLogic();

	//input
	mApplicationBreslin->processInput();

	//network
	mApplicationBreslin->runNetwork(mApplicationBreslin->getRenderTime() * 1000.0f);

	if (mApplicationBreslin->mPlayingGame)
	{
		//game
		mApplicationBreslin->mGame->run();
	}

	//graphics
	if (!mApplicationBreslin->runGraphics())
	{
		//break;
	}

}
void ApplicationGlobal::exit()
{
}
