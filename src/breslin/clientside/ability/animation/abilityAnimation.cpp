#include "abilityAnimation.h"
#include "../../shape/dynamicShape.h"

#include "../../states/dynamicShapeStateMachine.h"
#include "abilityAnimationStates.h"

abilityAnimation::abilityAnimation(DynamicShape* shape)  : Ability(shape)
{
	//animation interpolateTick states
    mAnimationInterpolateTickStateMachine = new DynamicShapeStateMachine(shape);    //setup the state machine
    mAnimationInterpolateTickStateMachine->setCurrentState (Idle_InterpolateTick_Animation::Instance());
    mAnimationInterpolateTickStateMachine->setPreviousState(Idle_InterpolateTick_Animation::Instance());
    mAnimationInterpolateTickStateMachine->setGlobalState  (Global_InterpolateTick_Animation::Instance());  

}

abilityAnimation::~abilityAnimation()
{
}

void abilityAnimation::update()
{
	mAnimationInterpolateTickStateMachine->update();
}
