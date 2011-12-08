//header
#include "applicationPlay.h"

//log
#include "../../tdreamsock/dreamSockLog.h"

//application
#include "../applicationBreslin.h"

//game
#include "../../game/game.h"

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

}
void ApplicationPlay::execute()
{
	if (mApplicationBreslin->mPlayingGame)
	{
		//game
		mApplicationBreslin->mGame->run();
	}
}
void ApplicationPlay::exit()
{
}
