#include "battle.h"
#include "../tdreamsock/dreamSockLog.h"

#include <string>

//Ogre headers
#include "Ogre.h"
using namespace Ogre;

//steering states
#include "states/battleStates.h"

//shapes
#include "../shape/shape.h"

Battle::Battle(Shape* shape1, Shape* shape2)
{
	mShape1 = NULL;
	mShape2 = NULL;

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

