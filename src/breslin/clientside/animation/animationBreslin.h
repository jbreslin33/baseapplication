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
class AnimationBreslin : public BaseEntity 
{
public:

	AnimationBreslin(Shape* shape);
	~AnimationBreslin();

/******************************************************
*				VARIABLES
********************************************************/
//shape
Shape* mShape;

//state machines
StateMachine<AnimationBreslin>* mStateMachine;


/******************************************************
*				METHODS
********************************************************/

//updating
void processTick();
void interpolateTick(float renderTime);

//animation
virtual void     runAnimationBreslins        (                          ) = 0;  

//update
virtual void update() { }

//handle letter
virtual bool  handleLetter(Letter* letter) { }

//animations
virtual void run() { };
virtual void idle() { };

};

#endif
