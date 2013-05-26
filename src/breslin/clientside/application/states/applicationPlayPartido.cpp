//header
#include "applicationPlayPartido.h"

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
ApplicationPlayPartido::ApplicationPlayPartido(ApplicationPartido* applicationPartido) : ApplicationPlay(applicationPartido)
{
	mApplicationPartido = applicationPartido;
}

ApplicationPlayPartido::~ApplicationPlayPartido()
{

}

void ApplicationPlayPartido::enter()
{
	ApplicationPlay::enter();
}
void ApplicationPlayPartido::execute()
{
	ApplicationPlay::execute();
}

void ApplicationPlayPartido::exit()
{
	ApplicationPlay::exit();
}
