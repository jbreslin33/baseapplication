//header
#include "abilityRotationStates.h"

//log
#include "../../tdreamsock/dreamSockLog.h"

//state machine
#include "abilityRotationStateMachine.h"

//shape
#include "../../shape/shapeDynamic.h"

//title
#include "../../billboard/objectTitle.h"

//ability
#include "abilityRotation.h"

//game
#include "../../game/game.h"

/******************************************************
*				INTERPOLATE
*
*				   STATES
*
********************************************************/


/******************************************************
*				GLOBAL
********************************************************/
Global_ProcessTick_Rotation* Global_ProcessTick_Rotation::Instance()
{
  static Global_ProcessTick_Rotation instance;
  return &instance;
}
void Global_ProcessTick_Rotation::enter(AbilityRotation* abilityRotation)
{
}
void Global_ProcessTick_Rotation::execute(AbilityRotation* abilityRotation)
{
	//this will move the ghost shape to server position before we do anything with non-ghosts.
	abilityRotation->mShapeDynamic->mGhost->setRotation(abilityRotation->mShapeDynamic->mServerFrame->mRotation);
	abilityRotation->calculateDeltaRotation();
}
void Global_ProcessTick_Rotation::exit(AbilityRotation* abilityRotation)
{
}

/******************************************************
*				NORMAL
********************************************************/

Normal_ProcessTick_Rotation* Normal_ProcessTick_Rotation::Instance()
{
  static Normal_ProcessTick_Rotation instance;
  return &instance;
}
void Normal_ProcessTick_Rotation::enter(AbilityRotation* abilityRotation)
{

}
void Normal_ProcessTick_Rotation::execute(AbilityRotation* abilityRotation)
{
	abilityRotation->mShapeDynamic->appendToTitle("R:Normal");
	// if distance exceeds threshold && server velocity is zero
	if(abilityRotation->mDeltaRotation > abilityRotation->mRotInterpLimitHigh &&
		!abilityRotation->mShapeDynamic->mServerFrame->mRotationVelocity->isZero())
	{
		abilityRotation->mProcessTickStateMachine->changeState(Catchup_ProcessTick_Rotation::Instance());
    }
	else //server stopped or we are in sync so just use server vel as is..
    {
		Vector3D serverDest;

		serverDest.x = abilityRotation->mShapeDynamic->mServerFrame->mRotationVelocity->x;
	    serverDest.y = 0.0;
        serverDest.z = abilityRotation->mShapeDynamic->mServerFrame->mRotationVelocity->z;
        serverDest.normalise();

        if(abilityRotation->mShapeDynamic->mCommandToRunOnShape->mMilliseconds != 0)
        {
			
			abilityRotation->mSpeed =
			sqrt(
			pow(abilityRotation->mShapeDynamic->mServerFrame->mRotationVelocity->x, 2) + 
			pow(abilityRotation->mShapeDynamic->mServerFrame->mRotationVelocity->z, 2)) /
			abilityRotation->mShapeDynamic->mCommandToRunOnShape->mMilliseconds;
        }

        serverDest = serverDest * abilityRotation->mSpeed;

		abilityRotation->mShapeDynamic->mCommandToRunOnShape->mRotationVelocity->x = serverDest.x;
        abilityRotation->mShapeDynamic->mCommandToRunOnShape->mRotationVelocity->y = 0.0f;
        abilityRotation->mShapeDynamic->mCommandToRunOnShape->mRotationVelocity->z = serverDest.z;
	}
}
void Normal_ProcessTick_Rotation::exit(AbilityRotation* abilityRotation)
{
}

/******************************************************
*				CATCHUP
********************************************************/

Catchup_ProcessTick_Rotation* Catchup_ProcessTick_Rotation::Instance()
{
  static Catchup_ProcessTick_Rotation instance;
  return &instance;
}
void Catchup_ProcessTick_Rotation::enter(AbilityRotation* abilityRotation)
{
}
void Catchup_ProcessTick_Rotation::execute(AbilityRotation* abilityRotation)
{
	abilityRotation->mShapeDynamic->appendToTitle("R:Catchup");

	//if we are back in sync
	if(abilityRotation->mDeltaRotation <= abilityRotation->mRotInterpLimitHigh ||
		abilityRotation->mShapeDynamic->mServerFrame->mRotationVelocity->isZero())
    {
		abilityRotation->mProcessTickStateMachine->changeState(Normal_ProcessTick_Rotation::Instance());
    }
    else
    {
		Vector3D serverDest; //vector to future server pos
        Vector3D myDest; //vector from clienr pos to future server pos

        serverDest.x = abilityRotation->mShapeDynamic->mServerFrame->mRotationVelocity->x;
        serverDest.y = 0.0f;
        serverDest.z = abilityRotation->mShapeDynamic->mServerFrame->mRotationVelocity->z;
        serverDest.normalise();

        float multiplier = abilityRotation->mDeltaRotation * abilityRotation->mRotationInterpFactor;
        serverDest = serverDest * multiplier;
        serverDest.x = abilityRotation->mShapeDynamic->mServerFrame->mPosition->x + serverDest.x;
        serverDest.y = 0.0f;
        serverDest.z = abilityRotation->mShapeDynamic->mServerFrame->mPosition->z + serverDest.z;
       
		myDest.x = serverDest.x - abilityRotation->mShapeDynamic->getPosition().x;
        myDest.y = 0.0f;
        myDest.z = serverDest.z - abilityRotation->mShapeDynamic->getPosition().z;


        //dist from clienr pos to future server pos
        float predictDist = pow(myDest.x, 2) + pow(myDest.y, 2) + pow(myDest.z, 2);
        predictDist = sqrt(predictDist);

        //server velocity
		if(abilityRotation->mShapeDynamic->mCommandToRunOnShape->mMilliseconds != 0)
        {
			abilityRotation->mSpeed = sqrt(
				pow(abilityRotation->mShapeDynamic->mServerFrame->mRotationVelocity->x, 2) + 
				pow(abilityRotation->mShapeDynamic->mServerFrame->mRotationVelocity->z, 2)) /
				abilityRotation->mShapeDynamic->mCommandToRunOnShape->mMilliseconds;
			
			abilityRotation->mShapeDynamic->mSpeed = abilityRotation->mSpeed;
		}

		if(abilityRotation->mSpeed != 0.0)
		{
           //time needed to get to future server pos
           float time = abilityRotation->mDeltaRotation *
			   abilityRotation->mRotationInterpFactor/abilityRotation->mSpeed;

           myDest.normalise();

           //client vel needed to get to future server pos in time
		   float distTime = predictDist/time;
           myDest = myDest * distTime;

           abilityRotation->mShapeDynamic->mCommandToRunOnShape->mRotationVelocity->x = myDest.x;
           abilityRotation->mShapeDynamic->mCommandToRunOnShape->mRotationVelocity->y = 0.0f;
           abilityRotation->mShapeDynamic->mCommandToRunOnShape->mRotationVelocity->z = myDest.z;

		}
		else
		{
			//why would catchup ever need to set velocity to zero, wouldn't we simply leave catchup state??
           abilityRotation->mShapeDynamic->mCommandToRunOnShape->mRotationVelocity->x = 0.0;
           abilityRotation->mShapeDynamic->mCommandToRunOnShape->mRotationVelocity->y = 0.0;
           abilityRotation->mShapeDynamic->mCommandToRunOnShape->mRotationVelocity->z = 0.0;

		}
	}	
}
void Catchup_ProcessTick_Rotation::exit(AbilityRotation* abilityRotation)
{
}

/******************************************************
*				INTERPOLATE
*
*				   STATES
*
********************************************************/


/******************************************************
*				Normal
********************************************************/
Normal_InterpolateTick_Rotation* Normal_InterpolateTick_Rotation::Instance()
{
  static Normal_InterpolateTick_Rotation instance;
  return &instance;
}
void Normal_InterpolateTick_Rotation::enter(AbilityRotation* abilityRotation)
{
}
void Normal_InterpolateTick_Rotation::execute(AbilityRotation* abilityRotation)
{

	Vector3D transVector;

    transVector.x = abilityRotation->mShapeDynamic->mCommandToRunOnShape->mRotationVelocity->x;
	transVector.y = 0.0;
    transVector.z = abilityRotation->mShapeDynamic->mCommandToRunOnShape->mRotationVelocity->z;

	transVector = transVector * abilityRotation->mShapeDynamic->mGame->getRenderTime() * 1000;
	Vector3D* newRotation = new Vector3D();
	newRotation->x = transVector.x + abilityRotation->mShapeDynamic->getRotation()->x;
	newRotation->y = 0.0;
	newRotation->z = transVector.z + abilityRotation->mShapeDynamic->getRotation()->z;

	abilityRotation->mShapeDynamic->setRotation(newRotation);


}
void Normal_InterpolateTick_Rotation::exit(AbilityRotation* abilityRotation)
{
}

