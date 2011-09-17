#ifndef ABILITYROTATION_H
#define ABILITYROTATION_H

/******************************************************
*				INCLUDES
********************************************************/
#include "../ability.h"
#include "../../../math/vector3D.h"

/******************************************************
*				FORWARD DECLARATIONS
********************************************************/
class AbilityRotationStateMachine;
class AbilityRotationState;
class ShapeDynamic;

/******************************************************
*				CLASS
********************************************************/
class AbilityRotation : public Ability
{
public:

	AbilityRotation(ShapeDynamic* shapeDynamic);
	~AbilityRotation();

/******************************************************
*				VARIABLES
********************************************************/
AbilityRotationStateMachine* mProcessTickStateMachine;
AbilityRotationStateMachine* mInterpolateTickStateMachine;

//shape
ShapeDynamic* mShapeDynamic;

//speed
float mSpeed;

//thresholds
float mRotInterpLimitHigh;  
float mRotationInterpFactor;

//deltas
float mDeltaX;  
float mDeltaZ;  
float mDeltaY; 
float mDeltaRotation; 



/******************************************************
*				METHODS
********************************************************/

//updating
void processTick();
void interpolateTick(float renderTime);

//rotation
void  calculateDeltaRotation();


};

#endif