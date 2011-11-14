#ifndef ABILITYMOVE_H
#define ABILITYMOVE_H

/******************************************************
*				INCLUDES
********************************************************/
#include "../ability.h"

/******************************************************
*				FORWARD DECLARATIONS
********************************************************/
class AbilityMoveStateMachine;
class AbilityMoveState;
class Shape;
class Vector3D;

/******************************************************
*				CLASS
********************************************************/
class AbilityMove : public Ability
{
public:

	AbilityMove(Shape* shape);
	~AbilityMove();

/******************************************************
*				VARIABLES
********************************************************/
//shapeDynamic
Shape* mShape;

//state machines
AbilityMoveStateMachine* mProcessTickStateMachine;
AbilityMoveStateMachine* mInterpolateTickStateMachine;

//speed
float mSpeed; 

//thresholds
float mPosInterpLimitHigh; 
float mPosInterpFactor; 
float mMaximunVelocity;

//deltas
float mDeltaX;  
float mDeltaZ;  
float mDeltaY; 
float mDeltaPosition; 

/******************************************************
*				METHODS
********************************************************/

//updating
void processTick();
void interpolateTick(float renderTime);

//move
void calculateDeltaPosition();  
float calcuateSpeed(Vector3D* velocity, int milliseconds);
void regulate(Vector3D* velocityToRegulate);
};

#endif