#include "abilityAnimation.h"
#include "../../shape/shapeDynamic.h"

#include "../../states/stateMachineShapeDynamic.h"
#include "abilityAnimationStates.h"

AbilityAnimation::AbilityAnimation(ShapeDynamic* shape)  : Ability(shape)
{
	//animation interpolateTick states
    mAnimationInterpolateTickStateMachine = new ShapeDynamicStateMachine(shape);    //setup the state machine
    mAnimationInterpolateTickStateMachine->setCurrentState (Idle_InterpolateTick_Animation::Instance());
    mAnimationInterpolateTickStateMachine->setPreviousState(Idle_InterpolateTick_Animation::Instance());
    mAnimationInterpolateTickStateMachine->setGlobalState  (Global_InterpolateTick_Animation::Instance());  

}

AbilityAnimation::~AbilityAnimation()
{
}

void AbilityAnimation::update()
{

}
void AbilityAnimation::processTick()
{

}
void AbilityAnimation::interpolateTick(float renderTime)
{
	mAnimationInterpolateTickStateMachine->update();
}
