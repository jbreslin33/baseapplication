#include "abilityMove.h"
#include "../../shape/shapeDynamic.h"
#include "../../command/command.h"

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

    //thresholds
    mPosInterpLimitHigh = .066f; //how far away from server till we try to catch up
    mPosInterpFactor    = 4.0f;

	//deltas
	mDeltaX        = 0.0; 
	mDeltaY		   = 0.0;
	mDeltaZ        = 0.0;
	mDeltaPosition = 0.0;

	//speed
	mSpeed     = 0.0;

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

	mDeltaX = mShapeDynamic->mServerFrame->mPosition->x - mShapeDynamic->getPosition().x;
    mDeltaY = mShapeDynamic->mServerFrame->mPosition->y - mShapeDynamic->getPosition().y;
    mDeltaZ = mShapeDynamic->mServerFrame->mPosition->z - mShapeDynamic->getPosition().z;

    //distance we are off from server
    mDeltaPosition = sqrt(pow(mDeltaX, 2) + pow(mDeltaY, 2) +  pow(mDeltaZ, 2));
}
