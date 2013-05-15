#include "abilityMove.h"

//log
#include "../../tdreamsock/dreamSockLog.h"

//shape
#include "../../shape/shape.h"

//command
#include "../../command/command.h"

//state machines
#include "abilityMoveStateMachine.h"

//states
#include "abilityMoveStates.h"

//std lib
#include <math.h>

AbilityMove::AbilityMove(Shape* shapeDynamic)  : Ability(shapeDynamic)
{
	mShape = shapeDynamic;

	//move processTick states
	mProcessTickStateMachine = new AbilityMoveStateMachine(this);    //setup the state machine
	mProcessTickStateMachine->setCurrentState      (Normal_ProcessTick_Move::Instance());
	mProcessTickStateMachine->setPreviousState     (Normal_ProcessTick_Move::Instance());
	mProcessTickStateMachine->setGlobalState       (Global_ProcessTick_Move::Instance());

	//move interpolateTick states
	mInterpolateTickStateMachine = new AbilityMoveStateMachine(this);    //setup the state machine
	mInterpolateTickStateMachine->setCurrentState      (Normal_InterpolateTick_Move::Instance());
	mInterpolateTickStateMachine->setPreviousState     (Normal_InterpolateTick_Move::Instance());
	//mInterpolateTickStateMachine->setGlobalState       (Global_InterpolateTick_Move::Instance());
	mInterpolateTickStateMachine->setGlobalState       (NULL);

    	//thresholds
    	mPosInterpLimitHigh = .066f; //how far away from server till we try to catch up
    	mPosInterpFactor    = 4.0f;
	mMaximunVelocity    = .003083f; //do not let velocity go above this in any direction.

	//deltas
	mDeltaX        = 0.0f; 
	mDeltaY	       = 0.0f;
	mDeltaZ        = 0.0f;
	mDeltaPosition = 0.0f;
}

AbilityMove::~AbilityMove()
{
}

/******************************************************
*				UPDATING
********************************************************/
void AbilityMove::processTick()
{
	mProcessTickStateMachine->update();
}
void AbilityMove::interpolateTick(float renderTime)
{
	mInterpolateTickStateMachine->update();
}

/******************************************************
*				MOVE
********************************************************/

void AbilityMove::calculateDeltaPosition()  //mov
{

	mDeltaX = mShape->mServerCommandCurrent->mPosition->x - mShape->getPosition()->x;
    	mDeltaY = mShape->mServerCommandCurrent->mPosition->y - mShape->getPosition()->y;
    	mDeltaZ = mShape->mServerCommandCurrent->mPosition->z - mShape->getPosition()->z;

    	//distance we are off from server
    	mDeltaPosition = sqrt(pow(mDeltaX, 2) + pow(mDeltaY, 2) +  pow(mDeltaZ, 2));
}

float AbilityMove::calculateSpeed(Vector3D* velocity, int frameTime)
{
	float speed = sqrt(
	pow(velocity->x, 2) + 
    	pow(velocity->y, 2) +
	pow(velocity->z, 2)) /
	frameTime;

	return speed;
}

void AbilityMove::regulate(Vector3D* velocityToRegulate)
{
	//x
	if (velocityToRegulate->x > mMaximunVelocity)
	{
		//velocityToRegulate->x = mMaximunVelocity;
		LogString("x>");

	}
	
	if (velocityToRegulate->x < mMaximunVelocity * -1)
	{
		//velocityToRegulate->x = mMaximunVelocity * -1;
		LogString("x<");
	}
	

	//z
	if (velocityToRegulate->z > mMaximunVelocity)
	{
		//velocityToRegulate->z = mMaximunVelocity;
		LogString("z>");
	}

	if (velocityToRegulate->z < mMaximunVelocity * -1)
	{
		//velocityToRegulate->z = mMaximunVelocity * -1;
		LogString("z<");
	}
}
