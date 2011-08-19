#include "abilityAnimationStates.h"
#include "../abilityStateMachine.h"

#include "../../shape/shapeDynamic.h"

#include "../../billboard/objectTitle.h"
#include "abilityAnimation.h"


/******************************************************
*				INTERPOLATE
*
*				   STATES
*
********************************************************/


/******************************************************
*				IDLE
********************************************************/

Idle_InterpolateTick_Animation* Idle_InterpolateTick_Animation::Instance()
{
  static Idle_InterpolateTick_Animation instance;
  return &instance;
}
void Idle_InterpolateTick_Animation::enter(Ability* ability)
{
	shapeDynamic->mAbilityAnimation->enterAnimationState(this);
}

void Idle_InterpolateTick_Animation::execute(Ability* ability)
{
	if (!shapeDynamic->mCommandToRunOnShape.mVelocity.isZero())
	{
		shapeDynamic->mAbilityAnimation->mAnimationInterpolateTickStateMachine->changeState(Run_InterpolateTick_Animation::Instance());
	}

	shapeDynamic->mAbilityAnimation->runAnimations();
}
void Idle_InterpolateTick_Animation::exit(Ability* ability)
{
}

/******************************************************
*				RUN
********************************************************/

Run_InterpolateTick_Animation* Run_InterpolateTick_Animation::Instance()
{
  static Run_InterpolateTick_Animation instance;
  return &instance;
}
void Run_InterpolateTick_Animation::enter(Ability* ability)
{
	shapeDynamic->mAbilityAnimation->enterAnimationState(this);
}
void Run_InterpolateTick_Animation::execute(Ability* ability)
{
	if (shapeDynamic->mCommandToRunOnShape.mVelocity.isZero())
	{
		shapeDynamic->mAbilityAnimation->mAnimationInterpolateTickStateMachine->changeState(Idle_InterpolateTick_Animation::Instance());
	}
	
	shapeDynamic->mAbilityAnimation->runAnimations();
}

void Run_InterpolateTick_Animation::exit(Ability* ability)
{
}


