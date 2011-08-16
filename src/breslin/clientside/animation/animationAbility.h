#ifndef ANIMATIONABILITY_H
#define ANIMATIONABILITY_H

#include "../ability/ability.h"

class DynamicShapeStateMachine;
class DynamicShapeState;
class DynamicShape;

class AnimationAbility : public Ability
{
public:

	AnimationAbility(DynamicShape* shape);
	~AnimationAbility();

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
};

#endif