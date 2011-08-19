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
class ShapeDynamic;

/******************************************************
*				INCLUDES
********************************************************/
class AbilityAnimation : public Ability
{
public:

	AbilityAnimation(ShapeDynamic* shape);
	~AbilityAnimation();

/******************************************************
*				VARIABLES
********************************************************/
//shape
ShapeDynamic* mShapeDynamic;

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