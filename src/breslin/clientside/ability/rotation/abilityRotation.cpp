#include "abilityRotation.h"
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

	//////rotation
    mTurnSpeed = 250.0;

    mRotInterpLimitHigh = 6.0; //how far away from server till we try to catch up
    mRotInterpLimitLow  = 4.0; //how close to server till we are in sync
    mRotInterpIncrease  = 1.20f; //rot factor used to catchup to server
    mRotInterpDecrease  = 0.80f; //rot factor used to allow server to catchup to client

	//rotation
	mServerRotOld.zero();
	mServerRotNew.zero();
	mDegreesToServer = 0.0;

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

	mDeltaX = mShapeDynamic->mServerFrame->mPosition->x - mShapeDynamic->getRotation()->x;
    mDeltaY = mShapeDynamic->mServerFrame->mPosition->y - mShapeDynamic->getRotation()->y;
    mDeltaZ = mShapeDynamic->mServerFrame->mPosition->z - mShapeDynamic->getRotation()->z;

    //distance we are off from server
    mDeltaRotation = sqrt(pow(mDeltaX, 2) + pow(mDeltaY, 2) +  pow(mDeltaZ, 2));
}

float AbilityRotation::getDegreesToServer()  //rot
{
    Vector3D serverRotNew;

    serverRotNew.x = mShapeDynamic->mServerFrame->mRotation->x;
	serverRotNew.y = 0;
    serverRotNew.z = mShapeDynamic->mServerFrame->mRotation->z;

    serverRotNew.normalise();

    //calculate how far off we are from server
	float degreesToServer = mShapeDynamic->getDegreesToSomething(serverRotNew);

	return degreesToServer;
}

void AbilityRotation::calculateServerRotationSpeed()  //rot
{
    mServerRotOld.zero();
    mServerRotNew.zero();

    mServerRotOld.x = mShapeDynamic->mServerFrame->mRotationOld->x;
	mServerRotOld.y = 0;
    mServerRotOld.z = mShapeDynamic->mServerFrame->mRotationOld->z;

    mServerRotNew.x = mShapeDynamic->mServerFrame->mRotation->x;
	mServerRotNew.y = 0;
    mServerRotNew.z = mShapeDynamic->mServerFrame->mRotation->z;

    mServerRotNew.normalise();
    mServerRotOld.normalise();

    //calculate how far off we are from server
	mDegreesToServer = mShapeDynamic->getDegreesToSomething(mServerRotNew);

    //calculate server rotation from last tick to new one
	mServerRotSpeed = mShapeDynamic->mGhost->getDegreesToSomething(mServerRotNew);

    if(abs(mServerRotSpeed) < 0)
    {
		mServerRotSpeed = 0.0f;
    }
}
