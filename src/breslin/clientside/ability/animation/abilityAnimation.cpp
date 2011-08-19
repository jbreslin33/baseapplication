#include "abilityAnimation.h"
#include "../../shape/shapeDynamic.h"

#include "../abilityStateMachine.h"
#include "abilityAnimationStates.h"

AbilityAnimation::AbilityAnimation(ShapeDynamic* shape)  : Ability(shape)
{
	//animation interpolateTick states
    mAnimationInterpolateTickStateMachine = new ShapeDynamicStateMachine(shape);    //setup the state machine
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
