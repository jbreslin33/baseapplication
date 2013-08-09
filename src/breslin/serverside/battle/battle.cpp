#include "battle.h"
#include "../tdreamsock/dreamSockLog.h"

#include <string>

//Ogre headers
#include "Ogre.h"
using namespace Ogre;

//steering states
#include "states/battleStates.h"

Battle::Battle(Shape1* shape, Shape2* shape2)
{
	mShape1 = NULL;
	mShape2 = NULL;

 	//battle states
	mStateMachine =  new StateMachine<Battle>(this);
	mStateMachine->setCurrentState      (NORMAL_BATTLE::Instance());
	mStateMachine->setPreviousState     (NORMAL_BATTLE::Instance());
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

