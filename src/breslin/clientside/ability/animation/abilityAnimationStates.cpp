//parent
#include "abilityAnimationStates.h"

//log
#include "../../tdreamsock/dreamSockLog.h"

//state machine
#include "abilityAnimationStateMachine.h"

//shape
#include "../../shape/shape.h"

//billboard
#include "../../billboard/objectTitle.h"

//animation
#include "abilityAnimation.h"

//command
#include "../../command/command.h"

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
void Idle_InterpolateTick_Animation::enter(AbilityAnimation* abilityAnimation)
{
	abilityAnimation->enterAnimationState(this);
}

void Idle_InterpolateTick_Animation::execute(AbilityAnimation* abilityAnimation)
{
	if (!abilityAnimation->mShape->mCommandToRunOnShape->mVelocity->isZero())
	{
		LogString("IDLE");
		abilityAnimation->mAnimationInterpolateTickStateMachine->changeState(Run_InterpolateTick_Animation::Instance());
		
	}

	abilityAnimation->runAnimations();
}
void Idle_InterpolateTick_Animation::exit(AbilityAnimation* abilityAnimation)
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
void Run_InterpolateTick_Animation::enter(AbilityAnimation* abilityAnimation)
{
	abilityAnimation->enterAnimationState(this);
}
void Run_InterpolateTick_Animation::execute(AbilityAnimation* abilityAnimation)
{
	if (abilityAnimation->mShape->mCommandToRunOnShape->mVelocity->isZero())
	{
		abilityAnimation->mAnimationInterpolateTickStateMachine->changeState(Idle_InterpolateTick_Animation::Instance());
	}
	
	abilityAnimation->runAnimations();
}

void Run_InterpolateTick_Animation::exit(AbilityAnimation* abilityAnimation)
{
}


