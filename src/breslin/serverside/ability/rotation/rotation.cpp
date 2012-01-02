#include "rotation.h"
#include "../../tdreamsock/dreamSockLog.h"

#include "../../shape/shape.h"

#include <string>

//Ogre headers
#include "Ogre.h"
using namespace Ogre;

//rotation states
#include "rotationStateMachine.h"
#include "rotationStates.h"

Rotation::Rotation(Shape* shape) : Ability(shape)
{
	mShape = shape;

	mRotationSpeed  = 0.0;

    //run acceleration
    mRotationAccel    = .04166f * 100.0f;
    mRotationDecel    = .04166f * 100.0f;

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
	//LogString("rb:%f",mRotationSpeed);
	mRotationStateMachine->update();
	//LogString("ra:%f",mRotationSpeed);
}


