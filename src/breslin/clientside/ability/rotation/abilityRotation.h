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

//rotation
float mTurnSpeed; 
float mServerRotSpeed;  

float mRotInterpLimitHigh;  
float mRotInterpLimitLow;  
float mRotInterpIncrease;   
float mRotInterpDecrease;  

//rotation
Vector3D mServerRotOld;  
Vector3D mServerRotNew;  
float    mDegreesToServer;  

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
float getDegreesToServer();  
void  calculateServerRotationSpeed(); 

};

#endif