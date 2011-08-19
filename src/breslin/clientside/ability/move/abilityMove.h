#ifndef ABILITYMOVE_H
#define ABILITYMOVE_H

/******************************************************
*				INCLUDES
********************************************************/
#include "../ability.h"

/******************************************************
*				FORWARD DECLARATIONS
********************************************************/
class ShapeDynamicStateMachine;
class ShapeDynamicState;
class ShapeDynamic;

/******************************************************
*				CLASS
********************************************************/
class AbilityMove : public Ability
{
public:

	AbilityMove(ShapeDynamic* shapeDynamic);
	~AbilityMove();

/******************************************************
*				VARIABLES
********************************************************/
//shapeDynamic
ShapeDynamic* mShapeDynamic;

//state machines
ShapeDynamicStateMachine* mMoveProcessTickStateMachine;
ShapeDynamicStateMachine* mMoveInterpolateTickStateMachine;

//run speed
float mRunSpeed; 
float mRunSpeedMax; 

//thresholds
float mPosInterpLimitHigh; 
float mPosInterpFactor; 

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
};

#endif