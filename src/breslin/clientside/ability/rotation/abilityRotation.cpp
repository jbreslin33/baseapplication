#include "abilityRotation.h"
#include "../../shape/shapeDynamic.h"

#include "../abilityStateMachine.h"
#include "abilityRotationStates.h"

AbilityRotation::AbilityRotation(ShapeDynamic* shapeDynamic)  : Ability(shapeDynamic)
{
	mShapeDynamic = shapeDynamic;

	//process tick rotation states
	mRotationProcessTickStateMachine = new ShapeDynamicStateMachine(shapeDynamic);    //setup the state machine
	mRotationProcessTickStateMachine->setCurrentState      (Normal_ProcessTick_Rotation::Instance());
	mRotationProcessTickStateMachine->setPreviousState     (Normal_ProcessTick_Rotation::Instance());
	mRotationProcessTickStateMachine->setGlobalState       (Global_ProcessTick_Rotation::Instance());

	//interpolate tick rotation states
	mRotationInterpolateTickStateMachine = new ShapeDynamicStateMachine(shapeDynamic);    //setup the state machine
	mRotationInterpolateTickStateMachine->setCurrentState      (Normal_InterpolateTick_Rotation::Instance());
	mRotationInterpolateTickStateMachine->setPreviousState     (Normal_ProcessTick_Rotation::Instance());

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

}

AbilityRotation::~AbilityRotation()
{
}

/******************************************************
*				UPDATING
********************************************************/
void AbilityRotation::processTick()
{
	mRotationProcessTickStateMachine->update();
}
void AbilityRotation::interpolateTick(float renderTime)
{
	mRotationInterpolateTickStateMachine->update();
}

/******************************************************
*				Rotation
********************************************************/

float AbilityRotation::getDegreesToServer()  //rot
{
    Vector3D serverRotNew;

    serverRotNew.x = mShapeDynamic->mServerFrame.mRot.x;
	serverRotNew.y = 0;
    serverRotNew.z = mShapeDynamic->mServerFrame.mRot.z;

    serverRotNew.normalise();

    //calculate how far off we are from server
	float degreesToServer = mShapeDynamic->getDegreesToSomething(serverRotNew);

	return degreesToServer;
}

void AbilityRotation::calculateServerRotationSpeed()  //rot
{
    mServerRotOld.zero();
    mServerRotNew.zero();

    mServerRotOld.x = mShapeDynamic->mServerFrame.mRotOld.x;
	mServerRotOld.y = 0;
    mServerRotOld.z = mShapeDynamic->mServerFrame.mRotOld.z;

    mServerRotNew.x = mShapeDynamic->mServerFrame.mRot.x;
	mServerRotNew.y = 0;
    mServerRotNew.z = mShapeDynamic->mServerFrame.mRot.z;

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