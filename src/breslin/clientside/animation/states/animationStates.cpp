//parent
#include "animationStates.h"

//log
#include "../../tdreamsock/dreamSockLog.h"

//shape
#include "../../shape/shape.h"

//billboard
#include "../../billboard/objectTitle.h"

//animation
#include "../animationBreslin.h"

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
void IDLE_INTERPOLATETICK_ANIMATION::enter(AnimationBreslin* animation)
{
	animation->enterAnimationState(this);
}

void IDLE_INTERPOLATETICK_ANIMATION::execute(AnimationBreslin* animation)
{
	{
	Vector3D* positionDiff = new Vector3D();
	positionDiff->subtract(animation->mShape->mServerCommandCurrent->mPosition, animation->mShape->mServerCommandLast->mPosition);
 	
	if (!positionDiff->isZero())
		animation->mStateMachine->changeState(RUN_INTERPOLATETICK_ANIMATION::Instance());
	}

	animation->runAnimations();
}
void IDLE_INTERPOLATETICK_ANIMATION::exit(AnimationBreslin* animation)
{
}
bool IDLE_INTERPOLATETICK_ANIMATION::onLetter(AnimationBreslin* animation, Letter* letter)
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
void RUN_INTERPOLATETICK_ANIMATION::enter(AnimationBreslin* animation)
{
	animation->enterAnimationState(this);
}
void RUN_INTERPOLATETICK_ANIMATION::execute(AnimationBreslin* animation)
{
		
	Vector3D* positionDiff = new Vector3D();
	positionDiff->subtract(animation->mShape->mServerCommandCurrent->mPosition, animation->mShape->mServerCommandLast->mPosition);
 	
	if (positionDiff->isZero())
	{
		animation->mStateMachine->changeState(IDLE_INTERPOLATETICK_ANIMATION::Instance());
	}
	
	animation->runAnimations();
}

void RUN_INTERPOLATETICK_ANIMATION::exit(AnimationBreslin* animation)
{
}

bool RUN_INTERPOLATETICK_ANIMATION::onLetter(AnimationBreslin* animation, Letter* letter)
{
        return true;
}

