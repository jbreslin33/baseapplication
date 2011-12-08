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
}

void ApplicationInitialize::execute()
{

}

void ApplicationInitialize::exit()
{
}
