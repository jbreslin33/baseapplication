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
	//LogString("STATE: ApplicationGlobal");
}
void ApplicationGlobal::execute()
{
	if (mApplicationBreslin->mSetup)
	{
		//check network
		mApplicationBreslin->checkForByteBuffer();

		//graphics
		mApplicationBreslin->runGraphics();
	}
}
void ApplicationGlobal::exit()
{
}
