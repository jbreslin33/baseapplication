//header
#include "applicationGameReset.h"

//log
#include "../../tdreamsock/dreamSockLog.h"

//application
#include "../applicationPartido.h"

//game
#include "../../game/gamePartido.h"

//state machine
#include "../../../statemachine/stateMachine.h"

//byteBuffer
#include "../../bytebuffer/byteBuffer.h"

//byteBuffer
#include "../../network/network.h"

/***************************************
*	CONSTRUCTORS
***************************************/
ApplicationGameReset::ApplicationGameReset(ApplicationBreslin* applicationBreslin) 
{
	mApplicationBreslin = applicationBreslin;
}

ApplicationGameReset::~ApplicationGameReset()
{

}

void ApplicationGameReset::enter()
{
}

void ApplicationGameReset::execute()
{
}

void ApplicationGameReset::exit()
{
}
