//header
#include "applicationInitializeGraphics.h"

//log
#include "../../tdreamsock/dreamSockLog.h"

//state machine
#include "../../../statemachine/stateMachine.h"

//states
#include "applicationMain.h"

//application
#include "../applicationBreslin.h"

/***************************************
*	CONSTRUCTORS		          
***************************************/
ApplicationInitializeGraphics::ApplicationInitializeGraphics(ApplicationBreslin* applicationBreslin)
{
	mApplicationBreslin = applicationBreslin;
}

ApplicationInitializeGraphics::~ApplicationInitializeGraphics()
{

}

void ApplicationInitializeGraphics::enter()
{
	mApplicationBreslin->createJoinButtons();
		
		mApplicationBreslin->mScreenStateMachine->changeState(mApplicationBreslin->mApplicationMain);
}

void ApplicationInitializeGraphics::execute()
{
	//if (mApplicationBreslin->mGraphicsRunning)
	//{
		// create all buttons
		
	//}


}

void ApplicationInitializeGraphics::exit()
{
}
