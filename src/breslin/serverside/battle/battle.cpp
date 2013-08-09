#include "battle.h"
#include "../tdreamsock/dreamSockLog.h"

#include <string>

//Ogre headers
#include "Ogre.h"
using namespace Ogre;

//steering states
#include "states/battleStates.h"

//shapes
#include "../client/robust/partido/clientPartido.h"

Battle::Battle(ClientPartido* client1, ClientPartido* client2)
{
	mClient1 = NULL;
	mClient2 = NULL;

 	//battle states
	mStateMachine =  new StateMachine<Battle>(this);
	mStateMachine->setCurrentState      (INIT_BATTLE::Instance());
	mStateMachine->setPreviousState     (INIT_BATTLE::Instance());
	mStateMachine->setGlobalState       (GLOBAL_BATTLE::Instance());

}

Battle::~Battle()
{
	delete mStateMachine;
}
void Battle::update()
{
	mStateMachine->update();
}

