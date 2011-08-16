#include "AnimationAbility.h"
#include "../../shape/dynamicShape.h"

#include "../../states/dynamicShapeStateMachine.h"
#include "dynamicShapeAnimationStates.h"

AnimationAbility::AnimationAbility(DynamicShape* shape)  : Ability(shape)
{
	//animation interpolateTick states
    mAnimationInterpolateTickStateMachine = new DynamicShapeStateMachine(shape);    //setup the state machine
    mAnimationInterpolateTickStateMachine->setCurrentState (Idle_InterpolateTick_Animation::Instance());
    mAnimationInterpolateTickStateMachine->setPreviousState(Idle_InterpolateTick_Animation::Instance());
    mAnimationInterpolateTickStateMachine->setGlobalState  (Global_InterpolateTick_Animation::Instance());  

}

AnimationAbility::~AnimationAbility()
{
}

void AnimationAbility::update()
{
	mAnimationInterpolateTickStateMachine->update();
}
