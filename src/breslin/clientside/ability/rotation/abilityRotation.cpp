#include "abilityRotation.h"

//log
#include "../../tdreamsock/dreamSockLog.h"

#include "../../shape/shapeDynamic.h"

#include "abilityRotationStateMachine.h"
#include "abilityRotationStates.h"

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
	mInterpolateTickStateMachine->setPreviousState     (Normal_InterpolateTick_Rotation::Instance());

	//////rotation
    mTurnSpeed = 250.0;

    mRotInterpLimitHigh = 6.0; //how far away from server till we try to catch up
    mRotInterpLimitLow  = 4.0; //how close to server till we are in sync
    mRotInterpIncrease  = 1.20f; //rot factor used to catchup to server
    mRotInterpDecrease  = 0.80f; //rot factor used to allow server to catchup to client

	//rotation
	mServerRotOld = new Vector3D();
	mServerRotNew = new Vector3D();
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
	mProcessTickStateMachine->update();
}
void AbilityRotation::interpolateTick(float renderTime)
{
	mInterpolateTickStateMachine->update();
}

/******************************************************
*				Rotation
********************************************************/

float AbilityRotation::getDegreesToServer()  //rot
{
    Vector3D* serverRotNew = new Vector3D();

    serverRotNew->x = mShapeDynamic->mServerFrame->mRot->x;
	serverRotNew->y = 0;
    serverRotNew->z = mShapeDynamic->mServerFrame->mRot->z;

    serverRotNew->normalise();

    //calculate how far off we are from server
	float degreesToServer = mShapeDynamic->getDegreesToSomething(serverRotNew);

	return degreesToServer;
}

void AbilityRotation::calculateServerRotationSpeed()  //rot
{
    mServerRotOld->zero();
    mServerRotNew->zero();

    mServerRotOld->x = mShapeDynamic->mServerFrame->mRotOld->x;
	mServerRotOld->y = 0;
    mServerRotOld->z = mShapeDynamic->mServerFrame->mRotOld->z;

    mServerRotNew->x = mShapeDynamic->mServerFrame->mRot->x;
	mServerRotNew->y = 0;
    mServerRotNew->z = mShapeDynamic->mServerFrame->mRot->z;
/*
	LogString("oldX:%f",mServerRotOld->x);
	LogString("oldY:%f",mServerRotOld->y);
	LogString("oldZ:%f",mServerRotOld->z);

	LogString("newX:%f",mServerRotNew->x);
	LogString("newY:%f",mServerRotNew->y);
	LogString("newZ:%f",mServerRotNew->z);
*/	

    mServerRotNew->normalise();
    mServerRotOld->normalise();

	LogString("oldX:%f",mServerRotOld->x);
	LogString("oldY:%f",mServerRotOld->y);
	LogString("oldZ:%f",mServerRotOld->z);

	LogString("newX:%f",mServerRotNew->x);
	LogString("newY:%f",mServerRotNew->y);
	LogString("newZ:%f",mServerRotNew->z);

    //calculate how far off we are from server
	mDegreesToServer = mShapeDynamic->getDegreesToSomething(mServerRotNew);

    //calculate server rotation from last tick to new one
	mServerRotSpeed = mShapeDynamic->mGhost->getDegreesToSomething(mServerRotNew);
	//LogString("getDegreesToSomething:%f",mServerRotSpeed);
    /*
	if(abs(mServerRotSpeed) < 0)
    {
		mServerRotSpeed = 0.0f;
    }
	*/
}
