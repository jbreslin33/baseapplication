#include "abilityAnimation.h"
#include "../../shape/shapeDynamic.h"

#include "abilityAnimationStateMachine.h"
#include "abilityAnimationStates.h"

AbilityAnimation::AbilityAnimation(ShapeDynamic* shapeDynamic)  : Ability(shapeDynamic)
{
	//shape
	mShapeDynamic = shapeDynamic;

	//animation interpolateTick states
    mAnimationInterpolateTickStateMachine = new AbilityAnimationStateMachine(this);    //setup the state machine
    mAnimationInterpolateTickStateMachine->setCurrentState (Idle_InterpolateTick_Animation::Instance());
    mAnimationInterpolateTickStateMachine->setPreviousState(Idle_InterpolateTick_Animation::Instance());
}

AbilityAnimation::~AbilityAnimation()
{
}

/******************************************************
*				UPDATING
********************************************************/
void AbilityAnimation::processTick()
{

}
void AbilityAnimation::interpolateTick(float renderTime)
{
	mAnimationInterpolateTickStateMachine->update();
}
