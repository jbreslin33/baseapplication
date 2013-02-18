//header
#include "abilityAnimation.h"

//shape
#include "../../shape/shape.h"

//state machine
#include "abilityAnimationStateMachine.h"

//states
#include "abilityAnimationStates.h"

AbilityAnimation::AbilityAnimation(Shape* shapeDynamic)  : Ability(shapeDynamic)
{
	//shape
	mShape = shapeDynamic;

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
