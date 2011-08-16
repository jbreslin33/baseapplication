#include "abilityAnimationStates.h"
#include "../../states/shapeDynamicStateMachine.h"

#include "../../shape/shapeDynamic.h"

#include "../../billboard/objectTitle.h"
#include "abilityAnimation.h"

/******************** Global_InterpolateTick_Animation *****************/
Global_InterpolateTick_Animation* Global_InterpolateTick_Animation::Instance()
{
  static Global_InterpolateTick_Animation instance;
  return &instance;
}
void Global_InterpolateTick_Animation::enter(DynamicShape* shapeDynamic)
{
}
void Global_InterpolateTick_Animation::execute(DynamicShape* shapeDynamic)
{

}
void Global_InterpolateTick_Animation::exit(DynamicShape* shapeDynamic)
{
}

/******************** Idle_InterpolateTick_Animation *****************/

Idle_InterpolateTick_Animation* Idle_InterpolateTick_Animation::Instance()
{
  static Idle_InterpolateTick_Animation instance;
  return &instance;
}
void Idle_InterpolateTick_Animation::enter(DynamicShape* shapeDynamic)
{
	shapeDynamic->mabilityAnimation->enterAnimationState(this);
}

void Idle_InterpolateTick_Animation::execute(DynamicShape* shapeDynamic)
{
	if (!shapeDynamic->mCommandToRunOnShape.mVelocity.isZero())
	{
		shapeDynamic->mabilityAnimation->mAnimationInterpolateTickStateMachine->changeState(Run_InterpolateTick_Animation::Instance());
	}

	shapeDynamic->mabilityAnimation->runAnimations();
}
void Idle_InterpolateTick_Animation::exit(DynamicShape* shapeDynamic)
{
}

/******************** Run_InterpolateTick_Animation *****************/

Run_InterpolateTick_Animation* Run_InterpolateTick_Animation::Instance()
{
  static Run_InterpolateTick_Animation instance;
  return &instance;
}
void Run_InterpolateTick_Animation::enter(DynamicShape* shapeDynamic)
{
	shapeDynamic->mabilityAnimation->enterAnimationState(this);
}
void Run_InterpolateTick_Animation::execute(DynamicShape* shapeDynamic)
{
	if (shapeDynamic->mCommandToRunOnShape.mVelocity.isZero())
	{
		shapeDynamic->mabilityAnimation->mAnimationInterpolateTickStateMachine->changeState(Idle_InterpolateTick_Animation::Instance());
	}
	
	shapeDynamic->mabilityAnimation->runAnimations();
}

void Run_InterpolateTick_Animation::exit(DynamicShape* shapeDynamic)
{
}


