//header
#include "applicationMain.h"


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
ApplicationMainPartido::ApplicationMainPartido(ApplicationBreslin* application) : ApplicationMain(application)
{
	mApplication = application;
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

	if (mApplication->mButtonHit == mApplication->mButtonJoinGameB)
	{
		mApplication->mButtonHit = NULL;
 		mApplication->mGame = new GamePartido(mApplication);
		mApplication->sendJoinGame(2);
		mApplication->mStateMachine->changeState(mApplication->mApplicationPlay);
	}
}

void ApplicationMainPartido::exit()
{
	ApplicationMain::exit();	
}

