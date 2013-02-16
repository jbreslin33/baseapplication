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

//thresholds
float mPosInterpLimitHigh; 
float mPosInterpFactor; 
float mMaximunVelocity;

float mDeltaPosition; 

private:

//deltas
float mDeltaX;  
float mDeltaZ;  
float mDeltaY; 


/******************************************************
*				METHODS
********************************************************/
public:
//updating
void processTick();
void interpolateTick(float renderTime);

//move
void calculateDeltaPosition();  
float calculateSpeed(Vector3D* velocity, int frameTime);
void regulate(Vector3D* velocityToRegulate);
};

#endif
