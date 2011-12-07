//header
#include "screenMain.h"


//log
#include "../../tdreamsock/dreamSockLog.h"

//application
#include "../applicationBreslin.h"

/***************************************
*	CONSTRUCTORS		          
***************************************/
ScreenMain::ScreenMain(ApplicationBreslin* applicationBreslin)
{
	mApplicationBreslin = applicationBreslin;
}

ScreenMain::~ScreenMain()
{

}


void ScreenMain::enter()
{
	mApplicationBreslin->loadJoinScreen();
}
void ScreenMain::execute()
{

}
void ScreenMain::exit()
{
}
