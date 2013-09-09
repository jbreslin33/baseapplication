//header
#include "animation.h"

//shape
#include "../../shape/shape.h"

//states
#include "states/animationStates.h"

Animation::Animation(Shape* shapeDynamic)  : Ability(shapeDynamic)
{
	//shape
	mShape = shapeDynamic;

	//animation interpolateTick states
    	mStateMachine = new StateMachine<Animation>(this);    //setup the state machine
    	mStateMachine->setCurrentState (IDLE_INTERPOLATETICK_ANIMATION::Instance());
    	mStateMachine->setPreviousState(IDLE_INTERPOLATETICK_ANIMATION::Instance());
}

Animation::~Animation()
{
}

void Animation::processTick()
{

}

void Animation::interpolateTick(float renderTime)
{
	mAnimationInterpolateTickStateMachine->update();
}
