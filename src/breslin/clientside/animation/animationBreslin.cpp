//header
#include "animationBreslin.h"

//shape
#include "../shape/shape.h"

//states
#include "states/animationStates.h"

AnimationBreslin::AnimationBreslin(Shape* shapeDynamic)  : BaseEntity(BaseEntity::getNextValidID())
{
	LogString("AnimationBreslin::AnimationBreslin");
	//shape
	mShape = shapeDynamic;

	//animation interpolateTick states
    	mStateMachine = new StateMachine<AnimationBreslin>(this);    //setup the state machine
    	mStateMachine->setCurrentState (IDLE_INTERPOLATETICK_ANIMATION::Instance());
    	mStateMachine->setPreviousState(IDLE_INTERPOLATETICK_ANIMATION::Instance());
}

AnimationBreslin::~AnimationBreslin()
{
}

void AnimationBreslin::processTick()
{

}

void AnimationBreslin::interpolateTick(float renderTime)
{
	mStateMachine->update();
}
