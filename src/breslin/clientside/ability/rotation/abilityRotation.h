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

/******************************************************
*				METHODS
********************************************************/

//updating
void processTick();
void interpolateTick(float renderTime);

//rotation
float getDegreesToServer();  
void  calculateServerRotationSpeed(); 

};

#endif