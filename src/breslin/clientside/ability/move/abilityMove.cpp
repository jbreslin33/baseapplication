#include "abilityMove.h"
#include "../../shape/shapeDynamic.h"
#include "../../../command/command.h"

#include "abilityMoveStateMachine.h"
#include "abilityMoveStates.h"

#include <math.h>

AbilityMove::AbilityMove(ShapeDynamic* shapeDynamic)  : Ability(shapeDynamic)
{
	mShapeDynamic = shapeDynamic;

	//move processTick states
	mMoveProcessTickStateMachine = new AbilityMoveStateMachine(this);    //setup the state machine
	mMoveProcessTickStateMachine->setCurrentState      (Normal_ProcessTick_Move::Instance());
	mMoveProcessTickStateMachine->setPreviousState     (Normal_ProcessTick_Move::Instance());
	mMoveProcessTickStateMachine->setGlobalState       (Global_ProcessTick_Move::Instance());

	//move interpolateTick states
	mMoveInterpolateTickStateMachine = new AbilityMoveStateMachine(this);    //setup the state machine
	mMoveInterpolateTickStateMachine->setCurrentState      (Normal_InterpolateTick_Move::Instance());
	mMoveInterpolateTickStateMachine->setPreviousState     (Normal_InterpolateTick_Move::Instance());
	//mMoveInterpolateTickStateMachine->setGlobalState       (Global_InterpolateTick_Move::Instance());
	mMoveInterpolateTickStateMachine->setGlobalState       (NULL);

    //thresholds
    mPosInterpLimitHigh = 8.0; //how far away from server till we try to catch up
    mPosInterpFactor    = 4.0;

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
	mMoveProcessTickStateMachine->update();
}
void AbilityMove::interpolateTick(float renderTime)
{
	mMoveInterpolateTickStateMachine->update();
}

/******************************************************
*				MOVE
********************************************************/

void AbilityMove::calculateDeltaPosition()  //mov
{

	mDeltaX = mShapeDynamic->mServerFrame.mOrigin.x - mShapeDynamic->getPosition().x;
    mDeltaY = mShapeDynamic->mServerFrame.mOrigin.y - mShapeDynamic->getPosition().y;
    mDeltaZ = mShapeDynamic->mServerFrame.mOrigin.z - mShapeDynamic->getPosition().z;

    //distance we are off from server
    mDeltaPosition = sqrt(pow(mDeltaX, 2) + pow(mDeltaY, 2) +  pow(mDeltaZ, 2));
}
