#include "rotation.h"
#include "../tdreamsock/dreamSockLog.h"

#include "../shape/shape.h"

#include <string>

//Ogre headers
#include "Ogre.h"
using namespace Ogre;

//rotation states
#include "rotationStateMachine.h"
#include "rotationStates.h"

//key defines prob should be changed to a variable if possible
#define KEY_UP					1
#define KEY_DOWN				2
#define KEY_LEFT				4
#define KEY_RIGHT				8
#define KEY_COUNTER_CLOCKWISE      16
#define KEY_CLOCKWISE              32

Rotation::Rotation()
:
	OgreShape()
{
	mRotationSpeed  = 0.0;

    //run acceleration
    mRotationAccel    = .04166 * 10;
    mRotationDecel    = .04166 * 10;

	//rotation states
	mRotationStateMachine = new RotationStateMachine(this);    //setup the state machine
	mRotationStateMachine->setCurrentState      (Normal_Rotation::Instance());
	mRotationStateMachine->setPreviousState     (Normal_Rotation::Instance());
	mRotationStateMachine->setGlobalState       (NULL);
}

Rotation::~Rotation()
{
}

void Rotation::processTick()
{
	mRotationStateMachine->update();
}


