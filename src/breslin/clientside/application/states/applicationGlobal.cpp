//header
#include "applicationGlobal.h"

//log
#include "../../tdreamsock/dreamSockLog.h"

//application
#include "../applicationBreslin.h"

//state machine
#include "../../../statemachine/stateMachine.h"

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
		//graphics
		mApplicationBreslin->runGraphics();

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
}
void ApplicationGlobal::exit()
{
}
