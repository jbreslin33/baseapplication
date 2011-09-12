#include "move.h"
#include "../tdreamsock/dreamSockLog.h"

#include "../../serverside/client/client.h"

#define MAX_RUN_SPEED 1.66           // character running speed in units per second

#include <string>

//Ogre headers
#include "Ogre.h"
using namespace Ogre;

//move states
#include "moveStateMachine.h"
#include "moveStates.h"

//key defines prob should be changed to a variable if possible
#define KEY_UP					1
#define KEY_DOWN				2
#define KEY_LEFT				4
#define KEY_RIGHT				8
#define KEY_COUNTER_CLOCKWISE      16
#define KEY_CLOCKWISE              32

Move::Move()
:
	OgreShape()
{
    //runSpeed
    mRunSpeed     = 0.0;

    //run acceleration
    mRunAccel    = .04166;
    mRunDecel    = .04166;


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


