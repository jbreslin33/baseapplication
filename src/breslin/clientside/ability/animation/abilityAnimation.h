#ifndef ABILITYANIMATION_H
#define ABILITYANIMATION_H

#include "../ability.h"

class ShapeDynamicStateMachine;
class ShapeDynamicState;
class ShapeDynamic;

class AbilityAnimation : public Ability
{
public:

	AbilityAnimation(ShapeDynamic* shape);
	~AbilityAnimation();

/******************************************************
*				VARIABLES
********************************************************/

ShapeDynamicStateMachine* mAnimationInterpolateTickStateMachine;

/******************************************************
*				METHODS
********************************************************/

//animation
virtual void enterAnimationState(ShapeDynamicState* animationState) = 0;
virtual void     runAnimations        (                          ) = 0;   

//virtual
void update();
void processTick();
void interpolateTick(float renderTime);

};

#endif