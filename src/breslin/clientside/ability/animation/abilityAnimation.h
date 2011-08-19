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
class AbilityStateMachine;
class AbilityState;

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

//state machine
AbilityStateMachine* mAnimationInterpolateTickStateMachine;

/******************************************************
*				METHODS
********************************************************/

//updating
void processTick();
void interpolateTick(float renderTime);

//animation
virtual void enterAnimationState(AbilityState* abilityState) = 0;
virtual void     runAnimations        (                          ) = 0;  

};

#endif