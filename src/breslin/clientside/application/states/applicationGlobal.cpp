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
ApplicationGlobal::ApplicationGlobal(ApplicationBreslin* application)
{
	mApplication = application;
}

ApplicationGlobal::~ApplicationGlobal()
{

}

void ApplicationGlobal::enter()
{

}

void ApplicationGlobal::execute()
{
	if (mApplication->mSetup)
	{
		//check network
		mApplication->checkForByteBuffer();

		//graphics
		mApplication->runGraphics();
	}
}
void ApplicationGlobal::exit()
{
}
