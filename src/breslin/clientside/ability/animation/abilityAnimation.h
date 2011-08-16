#ifndef ANIMATIONABILITY_H
#define ANIMATIONABILITY_H

#include "../ability.h"

class DynamicShapeStateMachine;
class DynamicShapeState;
class DynamicShape;

class abilityAnimation : public Ability
{
public:

	abilityAnimation(DynamicShape* shape);
	~abilityAnimation();

/******************************************************
*				VARIABLES
********************************************************/
DynamicShapeStateMachine* mAnimationInterpolateTickStateMachine;

/******************************************************
*				METHODS
********************************************************/

//animation
virtual void enterAnimationState(DynamicShapeState* animationState) = 0;
virtual void     runAnimations        (                          ) = 0;   

//virtual
void update();

};

#endif