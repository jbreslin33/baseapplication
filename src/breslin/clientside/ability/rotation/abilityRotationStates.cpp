#include "shapeDynamicRotationStates.h"
#include "shapeDynamicStateMachine.h"

#include "../shape/shapeDynamic.h"

#include "../billboard/objectTitle.h"

/******************** Global_ProcessTick_Rotation *****************/
Global_ProcessTick_Rotation* Global_ProcessTick_Rotation::Instance()
{
  static Global_ProcessTick_Rotation instance;
  return &instance;
}
void Global_ProcessTick_Rotation::enter(DynamicShape* shapeDynamic)
{
}
void Global_ProcessTick_Rotation::execute(DynamicShape* shapeDynamic)
{
	shapeDynamic->calculateServerRotationSpeed();

	//shape_replace
	shapeDynamic->mGhost->yaw(shapeDynamic->mServerRotSpeed,true);	

}
void Global_ProcessTick_Rotation::exit(DynamicShape* shapeDynamic)
{
}

/******************** Normal_ProcessTick_Rotation *****************/

Normal_ProcessTick_Rotation* Normal_ProcessTick_Rotation::Instance()
{
  static Normal_ProcessTick_Rotation instance;
  return &instance;
}
void Normal_ProcessTick_Rotation::enter(DynamicShape* shapeDynamic)
{
}
void Normal_ProcessTick_Rotation::execute(DynamicShape* shapeDynamic)
{
	//->mObjectTitleString.append("R:Normal");
	
	// are we too far off you need to change to catchup state
    if(abs(shapeDynamic->mDegreesToServer) > shapeDynamic->mRotInterpLimitHigh)
    {
       shapeDynamic->mRotationProcessTickStateMachine->changeState(Catchup_ProcessTick_Rotation::Instance());
		return;
    }
    else
    {
         if (shapeDynamic->mServerRotSpeed == 0.0)
         {
			shapeDynamic->mCommandToRunOnShape.mRotSpeed = 0.0;
         }
         else
         {
			// if server rot counter-clockwise hardcode server rot to +mTurnSpeed
            if(shapeDynamic->mServerRotSpeed > 0.0)
            {
				shapeDynamic->mCommandToRunOnShape.mRotSpeed =shapeDynamic->mTurnSpeed;
            }
			else //clockwise - set to -mTurnSpeed
            {
				shapeDynamic->mCommandToRunOnShape.mRotSpeed = -shapeDynamic->mTurnSpeed;
            }
		}
	}
}
void Normal_ProcessTick_Rotation::exit(DynamicShape* shapeDynamic)
{
}

/******************** Catchup_ProcessTick_Rotation *****************/

Catchup_ProcessTick_Rotation* Catchup_ProcessTick_Rotation::Instance()
{
  static Catchup_ProcessTick_Rotation instance;
  return &instance;
}
void Catchup_ProcessTick_Rotation::enter(DynamicShape* shapeDynamic)
{
}
void Catchup_ProcessTick_Rotation::execute(DynamicShape* shapeDynamic)
{
	//->mObjectTitleString.append("R:Catchup");

	// are we back on track
    if(abs(shapeDynamic->mDegreesToServer) < shapeDynamic->mRotInterpLimitLow)
    {
       shapeDynamic->mRotationProcessTickStateMachine->changeState(Normal_ProcessTick_Rotation::Instance());
		return;
    }
    else
    {
		if(shapeDynamic->mServerRotSpeed != 0.0)
        {
			// if server rot counter-clockwise hardcode server rot to +mTurnSpeed
            if(shapeDynamic->mServerRotSpeed > 0.0)
            {
				shapeDynamic->mCommandToRunOnShape.mRotSpeed = shapeDynamic->mTurnSpeed;
            }
            else //clockwise - set to -mTurnSpeed
            {
				shapeDynamic->mCommandToRunOnShape.mRotSpeed = -shapeDynamic->mTurnSpeed;
            }
			if(shapeDynamic->mDegreesToServer / shapeDynamic->mServerRotSpeed > 0.0)
            {
				shapeDynamic->mCommandToRunOnShape.mRotSpeed = shapeDynamic->mCommandToRunOnShape.mRotSpeed * shapeDynamic->mRotInterpIncrease;
            }
            else
            {
				shapeDynamic->mCommandToRunOnShape.mRotSpeed = shapeDynamic->mCommandToRunOnShape.mRotSpeed * shapeDynamic->mRotInterpDecrease;
            }
		}
        else if(shapeDynamic->mServerRotSpeed == 0.0)
        {
			if (shapeDynamic->mDegreesToServer > 0.0)
            {
				shapeDynamic->mCommandToRunOnShape.mRotSpeed = shapeDynamic->mTurnSpeed;
            }
            else //clockwise - set to -mTurnSpeed
            {
				shapeDynamic->mCommandToRunOnShape.mRotSpeed = -shapeDynamic->mTurnSpeed;
            }
		}
	}
}
void Catchup_ProcessTick_Rotation::exit(DynamicShape* shapeDynamic)
{
}

/******************** Global_InterpolateTick_Rotation *****************/


Global_InterpolateTick_Rotation* Global_InterpolateTick_Rotation::Instance()
{
  static Global_InterpolateTick_Rotation instance;
  return &instance;
}
void Global_InterpolateTick_Rotation::enter(DynamicShape* shapeDynamic)
{
}
void Global_InterpolateTick_Rotation::execute(DynamicShape* shapeDynamic)
{
	
}
void Global_InterpolateTick_Rotation::exit(DynamicShape* shapeDynamic)
{
}

/******************** Normal_InterpolateTick_Rotation *****************/

Normal_InterpolateTick_Rotation* Normal_InterpolateTick_Rotation::Instance()
{
  static Normal_InterpolateTick_Rotation instance;
  return &instance;
}
void Normal_InterpolateTick_Rotation::enter(DynamicShape* shapeDynamic)
{
}
void Normal_InterpolateTick_Rotation::execute(DynamicShape* shapeDynamic)
{

	//->mObjectTitleString.append("R:Normal");
	float rotSpeed = shapeDynamic->mCommandToRunOnShape.mRotSpeed * shapeDynamic->mRenderTime;
   shapeDynamic->yaw(rotSpeed, true);

    if (shapeDynamic->mServerRotSpeed == 0.0 && abs(shapeDynamic->getDegreesToServer()) < shapeDynamic->mRotInterpLimitLow)
    {
		shapeDynamic->mRotationInterpolateTickStateMachine->changeState(Off_InterpolateTick_Rotation::Instance());
    }

}
void Normal_InterpolateTick_Rotation::exit(DynamicShape* shapeDynamic)
{
}

/******************** Off_InterpolateTick_Rotation *****************/

Off_InterpolateTick_Rotation* Off_InterpolateTick_Rotation::Instance()
{
  static Off_InterpolateTick_Rotation instance;
  return &instance;
}
void Off_InterpolateTick_Rotation::enter(DynamicShape* shapeDynamic)
{
	shapeDynamic->mCommandToRunOnShape.mRotSpeed = 0.0;
}
void Off_InterpolateTick_Rotation::execute(DynamicShape* shapeDynamic)
{		
	//->mObjectTitleString.append("R:Off");
	if (abs(shapeDynamic->getDegreesToServer()) > shapeDynamic->mRotInterpLimitLow)
    {
		shapeDynamic->mRotationInterpolateTickStateMachine->changeState(Normal_InterpolateTick_Rotation::Instance());
    }
}
void Off_InterpolateTick_Rotation::exit(DynamicShape* shapeDynamic)
{
}

