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

IDLE_INTERPOLATETICK_ANIMATION* IDLE_INTERPOLATETICK_ANIMATION::Instance()
{
  static IDLE_INTERPOLATETICK_ANIMATION instance;
  return &instance;
}
void IDLE_INTERPOLATETICK_ANIMATION::enter(AnimationBreslin* animation)
{
	// start off in the idle state (top and bottom together)
        animation->setBaseAnimation(ANIM_IDLE_BASE,false);
        animation->setTopAnimation(ANIM_IDLE_TOP,false);

        // relax the hands since we're not holding anything
        animation->mAnims[ANIM_HANDS_RELAXED]->setEnabled(true);
}

void IDLE_INTERPOLATETICK_ANIMATION::execute(AnimationBreslin* animation)
{
	{
	Vector3D* positionDiff = new Vector3D();
	positionDiff->subtract(animation->mShape->mServerCommandCurrent->mPosition, animation->mShape->mServerCommandLast->mPosition);
 	
	if (!positionDiff->isZero())
		animation->mAnimationInterpolateTickStateMachine->changeState(RUN_INTERPOLATETICK_ANIMATION::Instance());
	}

	animation->runAnimations();
}
void IDLE_INTERPOLATETICK_ANIMATION::exit(AnimationBreslin* animation)
{
}

bool IDLE_INTERPOLATETICK_ANIMATION::onLetter(AnimationBreslin* animationBreslin, Letter* letter)
{
        return true;
}

RUN_INTERPOLATETICK_ANIMATION* RUN_INTERPOLATETICK_ANIMATION::Instance()
{
  static RUN_INTERPOLATETICK_ANIMATION instance;
  return &instance;
}
void RUN_INTERPOLATETICK_ANIMATION::enter(AnimationBreslin* animation)
{
	animation->setBaseAnimation(ANIM_RUN_BASE, true);
        animation->setTopAnimation(ANIM_RUN_TOP, true);

        // relax the hands since we're not holding anything
        if (!animation->mAnims[ANIM_HANDS_RELAXED]->getEnabled())
        {
                animation->mAnims[ANIM_HANDS_RELAXED]->setEnabled(true);
        }
}
void RUN_INTERPOLATETICK_ANIMATION::execute(AnimationBreslin* animation)
{
		
	Vector3D* positionDiff = new Vector3D();
	positionDiff->subtract(animation->mShape->mServerCommandCurrent->mPosition, animation->mShape->mServerCommandLast->mPosition);
 	
	if (positionDiff->isZero())
	{
		animation->mAnimationInterpolateTickStateMachine->changeState(g::Instance());
	}
	
	animation->runAnimations();
}

void RUN_INTERPOLATETICK_ANIMATION::exit(AnimationBreslin* animation)
{
}

bool RUN_INTERPOLATETICK_ANIMATION::onLetter(AnimationBreslin* animationBreslin, Letter* letter)
{
        return true;
}
