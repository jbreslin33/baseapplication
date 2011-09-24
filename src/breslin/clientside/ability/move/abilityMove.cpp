#include "abilityMove.h"

//log
#include "../../tdreamsock/dreamSockLog.h"

//shape
#include "../../shape/shapeDynamic.h"

//command
#include "../../command/command.h"

//state machines
#include "abilityMoveStateMachine.h"
#include "abilityMoveStates.h"

#include <math.h>

AbilityMove::AbilityMove(ShapeDynamic* shapeDynamic)  : Ability(shapeDynamic)
{
	mShapeDynamic = shapeDynamic;

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

	//speed
	mSpeed     = 0.0;

    //thresholds
    mPosInterpLimitHigh = .066f; //how far away from server till we try to catch up
    mPosInterpFactor    = 4.0f;
	mMaximunVelocity    = .002083; //do not let velocity go above this in any direction.

	//deltas
	mDeltaX        = 0.0; 
	mDeltaY		   = 0.0;
	mDeltaZ        = 0.0;
	mDeltaPosition = 0.0;
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

	mDeltaX = mShapeDynamic->mServerFrame->mPosition->x - mShapeDynamic->getPosition()->x;
    mDeltaY = mShapeDynamic->mServerFrame->mPosition->y - mShapeDynamic->getPosition()->y;
    mDeltaZ = mShapeDynamic->mServerFrame->mPosition->z - mShapeDynamic->getPosition()->z;

    //distance we are off from server
    mDeltaPosition = sqrt(pow(mDeltaX, 2) + pow(mDeltaY, 2) +  pow(mDeltaZ, 2));
}

float AbilityMove::calcuateSpeed(Vector3D* velocity, int milliseconds)
{
	float speed = sqrt(
	pow(velocity->x, 2) + 
    pow(velocity->y, 2) +
	pow(velocity->z, 2)) /
	milliseconds;

	return speed;
}

void AbilityMove::regulate(Vector3D* velocityToRegulate)
{
	if (velocityToRegulate->x > mMaximunVelocity)
	{
		LogString("x:%f",velocityToRegulate->x);
		velocityToRegulate->x = mMaximunVelocity;
	}
	
	if (velocityToRegulate->x < mMaximunVelocity * -1)
	{
		LogString("x:%f",velocityToRegulate->x);
		velocityToRegulate->x = mMaximunVelocity * -1;
	}
	
	if (velocityToRegulate->y > mMaximunVelocity)
	{
		LogString("y:%f",velocityToRegulate->y);
		velocityToRegulate->y = mMaximunVelocity;
	}

	if (velocityToRegulate->y < mMaximunVelocity * -1)
	{
		LogString("y:%f",velocityToRegulate->y);
		velocityToRegulate->y = mMaximunVelocity * -1;
	}
}