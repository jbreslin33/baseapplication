//header
#include "applicationInitialize.h"

//log
#include "../../tdreamsock/dreamSockLog.h"

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
	mApplicationBreslin->go();
	mApplicationBreslin->run();
	
	// create all buttons
	mApplicationBreslin->createJoinButtons();
}

void ApplicationInitialize::execute()
{
	if (mApplicationBreslin->mGraphicsRunning)
	{
		//mApplicationBreslin->changeState(m
	}
}

void ApplicationInitialize::exit()
{
}
