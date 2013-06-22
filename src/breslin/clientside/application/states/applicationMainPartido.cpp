//header
#include "applicationMainPartido.h"

//log
#include "../../tdreamsock/dreamSockLog.h"

//application
#include "../applicationPartido.h"

//game
#include "../../game/gamePartido.h"

//state machine
#include "../../../statemachine/stateMachine.h"

/***************************************
*	CONSTRUCTORS
***************************************/
ApplicationMainPartido::ApplicationMainPartido(ApplicationPartido* applicationPartido) : ApplicationMain(applicationPartido)
{
	mApplicationPartido = applicationPartido;
}

ApplicationMainPartido::~ApplicationMainPartido()
{

}

void ApplicationMainPartido::enter()
{
	ApplicationMain::enter();	
}

void ApplicationMainPartido::execute()
{
	ApplicationMain::execute();	

	if (mApplicationPartido->mButtonHit == mApplicationPartido->mButtonJoinGameB)
	{
		LogString("ApplicationMainPartido::execute....button hit for b"); 
		mApplicationPartido->mButtonHit = NULL;
 		mApplicationPartido->setGame(new GamePartido(mApplicationPartido));
 		mApplicationPartido->getGame()->createStates();
 		mApplicationPartido->getGame()->setStates();
		mApplicationPartido->sendJoinGame(2);
		mApplicationPartido->mStateMachine->changeState(mApplicationPartido->mApplicationPlay);
	}
}

void ApplicationMainPartido::exit()
{
	ApplicationMain::exit();	
}

