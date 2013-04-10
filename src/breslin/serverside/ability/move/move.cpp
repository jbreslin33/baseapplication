#include "move.h"
#include "../../tdreamsock/dreamSockLog.h"

#include "../../client/client.h"

#include <string>

//Ogre headers
#include "Ogre.h"
using namespace Ogre;

//move states
#include "moveStateMachine.h"
#include "moveStates.h"

Move::Move(Shape* shape) : Ability(shape)
{
	mShape = shape;

    //runSpeed
    mRunSpeed     = 0.0;


    //run acceleration
    mRunAccel    = .04166f * 50.5;
    mRunDecel    = .04166f * 50.5;


 	//move states
	mMoveStateMachine = new MoveStateMachine(this);    //setup the state machine
	mMoveStateMachine->setCurrentState      (Normal_Move::Instance());
	mMoveStateMachine->setPreviousState     (Normal_Move::Instance());
	mMoveStateMachine->setGlobalState       (NULL);
}

Move::~Move()
{
}
void Move::processTick()
{
	mMoveStateMachine->update();
}


