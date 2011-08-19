#ifndef ABILITYMOVE_H
#define ABILITYMOVE_H

#include "../ability.h"

class ShapeDynamicStateMachine;
class ShapeDynamicState;
class ShapeDynamic;

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
float mRunSpeed; //move
float mRunSpeedMax; //move

//thresholds
float mPosInterpLimitHigh; //mov
float mPosInterpFactor; //mov

//deltas
float mDeltaX;  //mov
float mDeltaZ;  //mov
float mDeltaY; //mov
float mDeltaPosition; //mov

/******************************************************
*				METHODS
********************************************************/


//updating
void processTick();
void interpolateTick(float renderTime);

//move
void calculateDeltaPosition();  //mov
};

#endif