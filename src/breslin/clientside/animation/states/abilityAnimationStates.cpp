//parent
#include "abilityAnimationOgreStates.h"

//log
#include "../../tdreamsock/dreamSockLog.h"

//state machine
#include "abilityAnimationOgreStateMachine.h"

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

IDLE_INTERPOLATETICK_ANIMATION* IDLE_INTERPOLATETICK_ANIMATION::Instance()
{
  static IDLE_INTERPOLATETICK_ANIMATION instance;
  return &instance;
}
void IDLE_INTERPOLATETICK_ANIMATION::enter(AbilityAnimationOgre* abilityAnimationOgre)
{
	abilityAnimationOgre->enterAnimationState(this);
}

void IDLE_INTERPOLATETICK_ANIMATION::execute(AbilityAnimationOgre* abilityAnimationOgre)
{
	{
	Vector3D* positionDiff = new Vector3D();
	positionDiff->subtract(abilityAnimationOgre->mShape->mServerCommandCurrent->mPosition, abilityAnimationOgre->mShape->mServerCommandLast->mPosition);
 	
	if (!positionDiff->isZero())
		abilityAnimationOgre->mAnimationInterpolateTickStateMachine->changeState(RUN_INTERPOLATETICK_ANIMATION::Instance());
	}

	abilityAnimationOgre->runAnimations();
}
void IDLE_INTERPOLATETICK_ANIMATION::exit(AbilityAnimationOgre* abilityAnimationOgre)
{
}
bool IDLE_INTERPOLATETICK_ANIMATION::onLetter(AbilityAnimationOgre* abilityAnimationOgre, Letter* letter)
{
        return true;
}

/******************************************************
*				RUN
********************************************************/

RUN_INTERPOLATETICK_ANIMATION* RUN_INTERPOLATETICK_ANIMATION::Instance()
{
  static RUN_INTERPOLATETICK_ANIMATION instance;
  return &instance;
}
void RUN_INTERPOLATETICK_ANIMATION::enter(AbilityAnimationOgre* abilityAnimationOgre)
{
	abilityAnimationOgre->enterAnimationState(this);
}
void RUN_INTERPOLATETICK_ANIMATION::execute(AbilityAnimationOgre* abilityAnimationOgre)
{
		
	Vector3D* positionDiff = new Vector3D();
	positionDiff->subtract(abilityAnimationOgre->mShape->mServerCommandCurrent->mPosition, abilityAnimationOgre->mShape->mServerCommandLast->mPosition);
 	
	if (positionDiff->isZero())
	{
		abilityAnimationOgre->mAnimationInterpolateTickStateMachine->changeState(IDLE_INTERPOLATETICK_ANIMATION::Instance());
	}
	
	abilityAnimationOgre->runAnimations();
}

void RUN_INTERPOLATETICK_ANIMATION::exit(AbilityAnimationOgre* abilityAnimationOgre)
{
}
bool RUN_INTERPOLATETICK_ANIMATION::onLetter(AbilityAnimationOgre* abilityAnimationOgre, Letter* letter)
{
        return true;
}


