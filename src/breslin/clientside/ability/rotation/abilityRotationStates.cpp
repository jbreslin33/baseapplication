//header
#include "abilityRotationStates.h"

//log
#include "../../tdreamsock/dreamSockLog.h"

//state machine
#include "abilityRotationStateMachine.h"

//shape
#include "../../shape/shape.h"

//title
#include "../../billboard/objectTitle.h"

//ability
#include "abilityRotation.h"

//game
#include "../../game/game.h"

//applicationBreslin
#include "../../application/applicationBreslin.h"

//command
#include "../../command/command.h"

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
	abilityRotation->mShape->mGhost->yaw(abilityRotation->mGhostSpeed,true);
	
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
	// abilityRotation->mShape->appendToTitle("R:Normal");
	
	// are we too far off you need to change to catchup state
    	if(abs(abilityRotation->mDegreesToServer) > abilityRotation->mRotInterpLimitHigh)
    	{
		abilityRotation->mProcessTickStateMachine->changeState(Catchup_ProcessTick_Rotation::Instance());
    	}
	if (abilityRotation->mServerRotSpeed == 0.0)
        {
		abilityRotation->mRotationSpeed = 0.0;
        }
        else
        {
		// if server rot counter-clockwise hardcode server rot to +mTurnSpeed
            	if(abilityRotation->mServerRotSpeed > 0.0)
            	{
			abilityRotation->mRotationSpeed = abilityRotation->mTurnSpeed;
            	}
		else //clockwise - set to -mTurnSpeed
            	{
			abilityRotation->mRotationSpeed = -abilityRotation->mTurnSpeed;
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
	// abilityRotation->mShape->appendToTitle("R:Catchup");
	// are we back on track
    	if(abs(abilityRotation->mDegreesToServer) < abilityRotation->mRotInterpLimitLow)
    	{
       		abilityRotation->mProcessTickStateMachine->changeState(Normal_ProcessTick_Rotation::Instance());
    	}
	
	if(abilityRotation->mServerRotSpeed != 0.0)
        {
			// if server rot counter-clockwise hardcode server rot to +mTurnSpeed
        	if(abilityRotation->mServerRotSpeed > 0.0)
            	{
			abilityRotation->mShape->mCommandToRunOnShape->mRotationSpeed = abilityRotation->mTurnSpeed;
            	}
            	else //clockwise - set to -mTurnSpeed
            	{
			abilityRotation->mShape->mCommandToRunOnShape->mRotationSpeed = -abilityRotation->mTurnSpeed;
            	}
		
		if(abilityRotation->mDegreesToServer / abilityRotation->mServerRotSpeed > 0.0)
            	{
			abilityRotation->mShape->mCommandToRunOnShape->mRotationSpeed = abilityRotation->mShape->mCommandToRunOnShape->mRotationSpeed * abilityRotation->mRotInterpIncrease;
            	}
            	else
            	{
			abilityRotation->mShape->mCommandToRunOnShape->mRotationSpeed = abilityRotation->mShape->mCommandToRunOnShape->mRotationSpeed * abilityRotation->mRotInterpDecrease;
       	     	}
	}
        else if (abilityRotation->mServerRotSpeed == 0.0)
        {
		if (abilityRotation->mDegreesToServer > 0.0)
            	{
			abilityRotation->mShape->mCommandToRunOnShape->mRotationSpeed = abilityRotation->mTurnSpeed;
            	}
            	else //clockwise - set to -mTurnSpeed
            	{
			abilityRotation->mShape->mCommandToRunOnShape->mRotationSpeed = -abilityRotation->mTurnSpeed;
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
	float rotSpeed = abilityRotation->mShape->mCommandToRunOnShape->mRotationSpeed * abilityRotation->mShape->mApplication->getRenderTime();
	abilityRotation->mShape->yaw(rotSpeed, true);

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
	abilityRotation->mRotationSpeed = 0.0;
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

