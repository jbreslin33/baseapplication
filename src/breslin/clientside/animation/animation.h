#ifndef ANIMATION_H
#define ANIMATION_H

//parent
#include "../../baseentity/baseEntity.h"

#include "../../fsm/stateMachine.h"

template <class entity_type> class State;

//shape
class Shape;

/******************************************************
*				INCLUDES
********************************************************/
class Animation : public BaseEntity 
{
public:

	Animation(Shape* shape);
	~Animation();

/******************************************************
*				VARIABLES
********************************************************/
//shape
Shape* mShape;

//state machines
StateMachine<Animation>* mInterpolateTickStateMachine;


/******************************************************
*				METHODS
********************************************************/

//updating
void processTick();
void interpolateTick(float renderTime);

//animation
virtual void enterAnimationState(AbilityAnimationState* abilityAnimationState) = 0;
virtual void     runAnimations        (                          ) = 0;  

//update
virtual void update() { }

//handle letter
virtual bool  handleLetter(Letter* letter) { }

};

#endif
