#ifndef ABILITYROTATION_H
#define ABILITYROTATION_H

#include "../ability.h"
#include "../../../math/vector3D.h"

class ShapeDynamicStateMachine;
class ShapeDynamicState;
class ShapeDynamic;

class AbilityRotation : public Ability
{
public:

	AbilityRotation(ShapeDynamic* shapeDynamic);
	~AbilityRotation();

/******************************************************
*				VARIABLES
********************************************************/
ShapeDynamicStateMachine* mRotationProcessTickStateMachine;
ShapeDynamicStateMachine* mRotationInterpolateTickStateMachine;

//shape
ShapeDynamic* mShapeDynamic;

//rotation
float mTurnSpeed; //rot
float mServerRotSpeed;  //rot

float mRotInterpLimitHigh;  //rot
float mRotInterpLimitLow;  //rot
float mRotInterpIncrease;   //rot
float mRotInterpDecrease;  //rot

//rotation
Vector3D mServerRotOld;  //rot
Vector3D mServerRotNew;  //rot
float    mDegreesToServer;  //rot
/******************************************************
*				METHODS
********************************************************/

//updating
void processTick();
void interpolateTick(float renderTime);

//rotation
float getDegreesToServer();  //rot
void  calculateServerRotationSpeed();  //rot

};

#endif