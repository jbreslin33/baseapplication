#include "dynamicShapeAnimationStates.h"
#include "../../states/dynamicShapeStateMachine.h"

#include "../../shape/dynamicShape.h"

#include "../../billboard/objectTitle.h"
#include "animationAbility.h"

/******************** Global_InterpolateTick_Animation *****************/
Global_InterpolateTick_Animation* Global_InterpolateTick_Animation::Instance()
{
  static Global_InterpolateTick_Animation instance;
  return &instance;
}
void Global_InterpolateTick_Animation::enter(DynamicShape* dynamicShape)
{
}
void Global_InterpolateTick_Animation::execute(DynamicShape* dynamicShape)
{

}
void Global_InterpolateTick_Animation::exit(DynamicShape* dynamicShape)
{
}

/******************** Idle_InterpolateTick_Animation *****************/

Idle_InterpolateTick_Animation* Idle_InterpolateTick_Animation::Instance()
{
  static Idle_InterpolateTick_Animation instance;
  return &instance;
}
void Idle_InterpolateTick_Animation::enter(DynamicShape* dynamicShape)
{
	dynamicShape->mAnimationAbility->enterAnimationState(this);
}

void Idle_InterpolateTick_Animation::execute(DynamicShape* dynamicShape)
{
	if (!dynamicShape->mCommandToRunOnShape.mVelocity.isZero())
	{
		dynamicShape->mAnimationAbility->mAnimationInterpolateTickStateMachine->changeState(Run_InterpolateTick_Animation::Instance());
	}

	dynamicShape->mAnimationAbility->runAnimations();
}
void Idle_InterpolateTick_Animation::exit(DynamicShape* dynamicShape)
{
}

/******************** Run_InterpolateTick_Animation *****************/

Run_InterpolateTick_Animation* Run_InterpolateTick_Animation::Instance()
{
  static Run_InterpolateTick_Animation instance;
  return &instance;
}
void Run_InterpolateTick_Animation::enter(DynamicShape* dynamicShape)
{
	dynamicShape->mAnimationAbility->enterAnimationState(this);
}
void Run_InterpolateTick_Animation::execute(DynamicShape* dynamicShape)
{
	if (dynamicShape->mCommandToRunOnShape.mVelocity.isZero())
	{
		dynamicShape->mAnimationAbility->mAnimationInterpolateTickStateMachine->changeState(Idle_InterpolateTick_Animation::Instance());
	}
	
	dynamicShape->mAnimationAbility->runAnimations();
}

void Run_InterpolateTick_Animation::exit(DynamicShape* dynamicShape)
{
}


