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

//application
#include "../../game/application.h"

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
	abilityRotation->calculateServerRotationSpeed();
	abilityRotation->mShapeDynamic->mGhost->yaw(abilityRotation->mGhostSpeed,true);
	
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
	//->mObjectTitleString.append("R:Normal");
	
	// are we too far off you need to change to catchup state
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
				//LogString("N1:%f",abilityRotation->mShapeDynamic->mCommandToRunOnShape->mRotSpeed);
            }
			else //clockwise - set to -mTurnSpeed
            {
				abilityRotation->mShapeDynamic->mCommandToRunOnShape->mRotSpeed = -abilityRotation->mTurnSpeed;
				//LogString("N2:%f",abilityRotation->mShapeDynamic->mCommandToRunOnShape->mRotSpeed);
            }
		}
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
				//LogString("C1:%f",abilityRotation->mShapeDynamic->mCommandToRunOnShape->mRotSpeed);
            }
            else //clockwise - set to -mTurnSpeed
            {
				abilityRotation->mShapeDynamic->mCommandToRunOnShape->mRotSpeed = -abilityRotation->mTurnSpeed;
				//LogString("C2:%f",abilityRotation->mShapeDynamic->mCommandToRunOnShape->mRotSpeed);
            }
			if(abilityRotation->mDegreesToServer / abilityRotation->mServerRotSpeed > 0.0)
            {
				abilityRotation->mShapeDynamic->mCommandToRunOnShape->mRotSpeed = abilityRotation->mShapeDynamic->mCommandToRunOnShape->mRotSpeed * abilityRotation->mRotInterpIncrease;
				//LogString("C3:%f",abilityRotation->mShapeDynamic->mCommandToRunOnShape->mRotSpeed);
            }
            else
            {
				abilityRotation->mShapeDynamic->mCommandToRunOnShape->mRotSpeed = abilityRotation->mShapeDynamic->mCommandToRunOnShape->mRotSpeed * abilityRotation->mRotInterpDecrease;
				//LogString("C4:%f",abilityRotation->mShapeDynamic->mCommandToRunOnShape->mRotSpeed);
            }
		}
        else if(abilityRotation->mServerRotSpeed == 0.0)
        {
			if (abilityRotation->mDegreesToServer > 0.0)
            {
				abilityRotation->mShapeDynamic->mCommandToRunOnShape->mRotSpeed = abilityRotation->mTurnSpeed;
				//LogString("C5:%f",abilityRotation->mShapeDynamic->mCommandToRunOnShape->mRotSpeed);
            }
            else //clockwise - set to -mTurnSpeed
            {
				abilityRotation->mShapeDynamic->mCommandToRunOnShape->mRotSpeed = -abilityRotation->mTurnSpeed;
				//LogString("C6:%f",abilityRotation->mShapeDynamic->mCommandToRunOnShape->mRotSpeed);
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
	//->mObjectTitleString.append("R:Normal");
	float rotSpeed = abilityRotation->mShapeDynamic->mCommandToRunOnShape->mRotSpeed * abilityRotation->mShapeDynamic->mGame->mApplication->getRenderTime();
	abilityRotation->mShapeDynamic->yaw(rotSpeed, true);

	if (abilityRotation->mServerRotSpeed == 0.0 && abs(abilityRotation->getDegreesToServer()) < abilityRotation->mRotInterpLimitLow)
    {
		abilityRotation->mInterpolateTickStateMachine->changeState(Off_InterpolateTick_Rotation::Instance());
    }
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
	//LogString("OF:%f",abilityRotation->mShapeDynamic->mCommandToRunOnShape->mRotSpeed);
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

