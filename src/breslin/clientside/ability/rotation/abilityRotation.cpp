#include "abilityRotation.h"

//log
#include "../../tdreamsock/dreamSockLog.h"

#include "../../shape/shapeDynamic.h"

#include "abilityRotationStateMachine.h"
#include "abilityRotationStates.h"

#include <math.h>

#ifdef WIN32
//do nothing
#else
#include <stdlib.h>
#endif

AbilityRotation::AbilityRotation(ShapeDynamic* shapeDynamic)  : Ability(shapeDynamic)
{
	mShapeDynamic = shapeDynamic;

	//process tick rotation states
	mProcessTickStateMachine = new AbilityRotationStateMachine(this);    //setup the state machine
	mProcessTickStateMachine->setCurrentState      (Normal_ProcessTick_Rotation::Instance());
	mProcessTickStateMachine->setPreviousState     (Normal_ProcessTick_Rotation::Instance());
	mProcessTickStateMachine->setGlobalState       (Global_ProcessTick_Rotation::Instance());

	//interpolate tick rotation states
	mInterpolateTickStateMachine = new AbilityRotationStateMachine(this);    //setup the state machine
	mInterpolateTickStateMachine->setCurrentState      (Normal_InterpolateTick_Rotation::Instance());
	mInterpolateTickStateMachine->setPreviousState     (Normal_ProcessTick_Rotation::Instance());
//notes..close but the client is having trouble keeping up with rotation especially when max speed on server reaches
	//250 which is what it's set to. I think the throttle on the client needs to be upped.
	//speed
	mSpeed = 0.0f;

	//thresholds
	mRotInterpLimitHigh   = .066f; //how far away from server till we try to catch up
	mRotationInterpFactor = 4.0f;

	//deltas
	mDeltaX        = 0.0; 
	mDeltaY		   = 0.0;
	mDeltaZ        = 0.0;
	mDeltaRotation = 0.0;

}

AbilityRotation::~AbilityRotation()
{
}

/******************************************************
*				UPDATING
********************************************************/
void AbilityRotation::processTick()
{
	mProcessTickStateMachine->update();
}
void AbilityRotation::interpolateTick(float renderTime)
{
	mInterpolateTickStateMachine->update();
}

/******************************************************
*				Rotation
********************************************************/

void AbilityRotation::calculateDeltaRotation()  
{

	mDeltaX = mShapeDynamic->mServerFrame->mRotation->x - mShapeDynamic->getRotation()->x;
    mDeltaZ = mShapeDynamic->mServerFrame->mRotation->z - mShapeDynamic->getRotation()->z;
	
	//LogString("mRotationX:%f",mShapeDynamic->mServerFrame->mRotation->x);
	//LogString("getRotationZ:%f",mShapeDynamic->getRotation()->z);
	//LogString("mDeltaX:%f",mDeltaX);


	//LogString("mDeltaZ:%f",mDeltaZ);


    //distance we are off from server
    mDeltaRotation = sqrt(pow(mDeltaX, 2) + pow(mDeltaZ, 2));
}

