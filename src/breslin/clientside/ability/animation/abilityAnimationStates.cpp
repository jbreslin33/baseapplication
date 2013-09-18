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
#include "abilityAnimationOgre.h"

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
void Idle_InterpolateTick_Animation::enter(AbilityAnimationOgre* abilityAnimation)
{
	abilityAnimation->enterAnimationState(this);
}

void Idle_InterpolateTick_Animation::execute(AbilityAnimationOgre* abilityAnimation)
{
	{
	Vector3D* positionDiff = new Vector3D();
	positionDiff->subtract(abilityAnimation->mShape->mServerCommandCurrent->mPosition, abilityAnimation->mShape->mServerCommandLast->mPosition);
 	
	if (!positionDiff->isZero())
		abilityAnimation->mAnimationInterpolateTickStateMachine->changeState(Run_InterpolateTick_Animation::Instance());
	}

	abilityAnimation->runAnimations();
}
void Idle_InterpolateTick_Animation::exit(AbilityAnimationOgre* abilityAnimation)
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
void Run_InterpolateTick_Animation::enter(AbilityAnimationOgre* abilityAnimation)
{
	abilityAnimation->enterAnimationState(this);
}
void Run_InterpolateTick_Animation::execute(AbilityAnimationOgre* abilityAnimation)
{
		
	Vector3D* positionDiff = new Vector3D();
	positionDiff->subtract(abilityAnimation->mShape->mServerCommandCurrent->mPosition, abilityAnimation->mShape->mServerCommandLast->mPosition);
 	
	if (positionDiff->isZero())
	{
		abilityAnimation->mAnimationInterpolateTickStateMachine->changeState(Idle_InterpolateTick_Animation::Instance());
	}
	
	abilityAnimation->runAnimations();
}

void Run_InterpolateTick_Animation::exit(AbilityAnimationOgre* abilityAnimation)
{
}


