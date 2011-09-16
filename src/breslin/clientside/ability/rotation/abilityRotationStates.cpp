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
	//abilityRotation->calculateServerRotationSpeed();
	//abilityRotation->mShapeDynamic->mGhost->yaw(abilityRotation->mServerRotSpeed,true);
	
	//this will move the ghost shape to server position before we do anything with non-ghosts.
	abilityRotation->mShapeDynamic->mGhost->setRotation(abilityRotation->mShapeDynamic->mServerFrame->mRotation);
	//LogString("x:%f",abilityRotation->mShapeDynamic->mCommandToRunOnShape->mRotation->x);
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
	//LogString("mDeltaRotation:%f",abilityRotation->mDeltaRotation);
	//->mObjectTitleString.append("R:Normal");
	//NEW COPIED FROM MOVE
	/*
	if(abilityMove->mDeltaPosition > abilityMove->mPosInterpLimitHigh && !abilityMove->mShapeDynamic->mServerFrame->mMoveVelocity->isZero())
	{
		abilityMove->mProcessTickStateMachine->changeState(Catchup_ProcessTick_Move::Instance());
    }
    else //server stopped or we are in sync so just use server vel as is..
    {
	*/
		Vector3D serverDest;
       // Ogre::Vector3 myDest      = Ogre::Vector3::ZERO;

		serverDest.x = abilityRotation->mShapeDynamic->mServerFrame->mRotationVelocity->x;
	    serverDest.y = abilityRotation->mShapeDynamic->mServerFrame->mRotationVelocity->y;
        serverDest.z = abilityRotation->mShapeDynamic->mServerFrame->mRotationVelocity->z;
        serverDest.normalise();

       // abilityMove->mShapeDynamic->mSpeed = 0.0;

        if(abilityRotation->mShapeDynamic->mCommandToRunOnShape->mMilliseconds != 0)
        {
			
			abilityRotation->mSpeed =
			sqrt(
			pow(abilityRotation->mShapeDynamic->mServerFrame->mRotationVelocity->x, 2) + 
            pow(abilityRotation->mShapeDynamic->mServerFrame->mRotationVelocity->y, 2) +
			pow(abilityRotation->mShapeDynamic->mServerFrame->mRotationVelocity->z, 2)) /
			abilityRotation->mShapeDynamic->mCommandToRunOnShape->mMilliseconds;
        }

        serverDest = serverDest * abilityRotation->mSpeed;

		abilityRotation->mShapeDynamic->mCommandToRunOnShape->mRotationVelocity->x = serverDest.x;
        abilityRotation->mShapeDynamic->mCommandToRunOnShape->mRotationVelocity->y = serverDest.y;
        abilityRotation->mShapeDynamic->mCommandToRunOnShape->mRotationVelocity->z = serverDest.z;
	//}


//////OLD IS BELOW

	// are we too far off you need to change to catchup state
	/*
    if(abs(abilityRotation->mDegreesToServer) > abilityRotation->mRotInterpLimitHigh)
    {
		abilityRotation->mProcessTickStateMachine->changeState(Catchup_ProcessTick_Rotation::Instance());
		return;
    }
    else
    {
         if (abilityRotation->mServerRotSpeed == 0.0)
         {
			abilityRotation->mShapeDynamic->mCommandToRunOnShape->mRotSpeed = 0.0;
         }
         else
         {
			// if server rot counter-clockwise hardcode server rot to +mTurnSpeed
            if(abilityRotation->mServerRotSpeed > 0.0)
            {
				abilityRotation->mShapeDynamic->mCommandToRunOnShape->mRotSpeed = abilityRotation->mTurnSpeed;
            }
			else //clockwise - set to -mTurnSpeed
            {
				abilityRotation->mShapeDynamic->mCommandToRunOnShape->mRotSpeed = -abilityRotation->mTurnSpeed;
            }
		}
	}
	*/
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
	//->mObjectTitleString.append("R:Catchup");

	// are we back on track
    if(abs(abilityRotation->mDegreesToServer) < abilityRotation->mRotInterpLimitLow)
    {
       abilityRotation->mProcessTickStateMachine->changeState(Normal_ProcessTick_Rotation::Instance());
		return;
    }
    else
    {
		if(abilityRotation->mServerRotSpeed != 0.0)
        {
			// if server rot counter-clockwise hardcode server rot to +mTurnSpeed
            if(abilityRotation->mServerRotSpeed > 0.0)
            {
				abilityRotation->mShapeDynamic->mCommandToRunOnShape->mRotSpeed = abilityRotation->mTurnSpeed;
            }
            else //clockwise - set to -mTurnSpeed
            {
				abilityRotation->mShapeDynamic->mCommandToRunOnShape->mRotSpeed = -abilityRotation->mTurnSpeed;
            }
			if(abilityRotation->mDegreesToServer / abilityRotation->mServerRotSpeed > 0.0)
            {
				abilityRotation->mShapeDynamic->mCommandToRunOnShape->mRotSpeed = abilityRotation->mShapeDynamic->mCommandToRunOnShape->mRotSpeed * abilityRotation->mRotInterpIncrease;
            }
            else
            {
				abilityRotation->mShapeDynamic->mCommandToRunOnShape->mRotSpeed = abilityRotation->mShapeDynamic->mCommandToRunOnShape->mRotSpeed * abilityRotation->mRotInterpDecrease;
            }
		}
        else if(abilityRotation->mServerRotSpeed == 0.0)
        {
			if (abilityRotation->mDegreesToServer > 0.0)
            {
				abilityRotation->mShapeDynamic->mCommandToRunOnShape->mRotSpeed = abilityRotation->mTurnSpeed;
            }
            else //clockwise - set to -mTurnSpeed
            {
				abilityRotation->mShapeDynamic->mCommandToRunOnShape->mRotSpeed = -abilityRotation->mTurnSpeed;
            }
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
    //transVector->y = abilityRotation->mShapeDynamic->mCommandToRunOnShape->mRotationVelocity->y;
	transVector.y = 0.0;
    transVector.z = abilityRotation->mShapeDynamic->mCommandToRunOnShape->mRotationVelocity->z;
	LogString("x:%f",abilityRotation->mShapeDynamic->mCommandToRunOnShape->mRotationVelocity->x);

	transVector = transVector * abilityRotation->mShapeDynamic->mGame->getRenderTime() * 1000;
	Vector3D* newRotation = new Vector3D();
	newRotation->x = transVector.x + abilityRotation->mShapeDynamic->getRotation()->x;
	//newRotation->y = transVector.y + abilityRotation->mShapeDynamic->getRotation()->y;
	newRotation->y = 0.0;
	newRotation->z = transVector.z + abilityRotation->mShapeDynamic->getRotation()->z;
	

	LogString("x:%f",newRotation->x);
	LogString("z:%f",newRotation->z);
	abilityRotation->mShapeDynamic->setRotation(newRotation);

	//abilityRotation->
/*
	//->mObjectTitleString.append("R:Normal");
	float rotSpeed = abilityRotation->mShapeDynamic->mCommandToRunOnShape->mRotSpeed * abilityRotation->mShapeDynamic->mGame->getRenderTime();
   abilityRotation->mShapeDynamic->yaw(rotSpeed, true);

   if (abilityRotation->mServerRotSpeed == 0.0 && abs(abilityRotation->getDegreesToServer()) < abilityRotation->mRotInterpLimitLow)
    {
		abilityRotation->mInterpolateTickStateMachine->changeState(Off_InterpolateTick_Rotation::Instance());
    }
*/
}
void Normal_InterpolateTick_Rotation::exit(AbilityRotation* abilityRotation)
{
}

/******************************************************
*				OFF
********************************************************/

Off_InterpolateTick_Rotation* Off_InterpolateTick_Rotation::Instance()
{
  static Off_InterpolateTick_Rotation instance;
  return &instance;
}
void Off_InterpolateTick_Rotation::enter(AbilityRotation* abilityRotation)
{
	abilityRotation->mShapeDynamic->mCommandToRunOnShape->mRotSpeed = 0.0;
}
void Off_InterpolateTick_Rotation::execute(AbilityRotation* abilityRotation)
{		
	//->mObjectTitleString.append("R:Off");
	if (abs(abilityRotation->getDegreesToServer()) > abilityRotation->mRotInterpLimitLow)
    {
		abilityRotation->mInterpolateTickStateMachine->changeState(Normal_InterpolateTick_Rotation::Instance());
    }
}
void Off_InterpolateTick_Rotation::exit(AbilityRotation* abilityRotation)
{
}

