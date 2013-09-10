#ifndef ABILITYANIMATION_H
#define ABILITYANIMATION_H

/*************************************
*         INCLUDES
*************************************/
//parent
#include "../ability.h"

/*************************************
*         FORWARD DECLARATIONS
*************************************/

//states
class AbilityAnimationStateMachine;
class AbilityAnimationState;

//shape
class Shape;

/******************************************************
*				INCLUDES
********************************************************/
class AbilityAnimation : public Ability
{
public:

	AbilityAnimation(Shape* shape);
	~AbilityAnimation();

/******************************************************
*				VARIABLES
********************************************************/
//shape
Shape* mShape;

//state machine
AbilityAnimationStateMachine* mAnimationInterpolateTickStateMachine;

/******************************************************
*				METHODS
********************************************************/

//updating
void processTick();
void interpolateTick(float renderTime);

//animation
virtual void enterAnimationState(AbilityAnimationState* abilityAnimationState) = 0;
virtual void     runAnimations        (                          ) = 0;  

};

#endif
