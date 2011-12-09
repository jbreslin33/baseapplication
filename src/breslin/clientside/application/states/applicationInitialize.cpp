//header
#include "applicationInitialize.h"

//log
#include "../../tdreamsock/dreamSockLog.h"

//state machine
#include "../../../statemachine/stateMachine.h"

//states
#include "applicationInitializeGraphics.h"

//application
#include "../applicationBreslin.h"

/***************************************
*	CONSTRUCTORS		          
***************************************/
ApplicationInitialize::ApplicationInitialize(ApplicationBreslin* applicationBreslin)
{
	mApplicationBreslin = applicationBreslin;
}

ApplicationInitialize::~ApplicationInitialize()
{

}

void ApplicationInitialize::enter()
{
	LogString("STATE: ApplicationInitialize");
}

void ApplicationInitialize::execute()
{
	LogString("setup......................................................................................................");
	if (mApplicationBreslin->setup())
	{
		mApplicationBreslin->mSetup = true;
		mApplicationBreslin->mScreenStateMachine->changeState(mApplicationBreslin->mApplicationInitializeGraphics);
	}	
}

void ApplicationInitialize::exit()
{
}
