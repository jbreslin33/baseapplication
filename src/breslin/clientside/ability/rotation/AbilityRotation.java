package breslin.clientside.ability.rotation;

/******************************************************
*				INCLUDES
********************************************************/

//parent
import breslin.clientside.ability.Ability;

//shapes
import breslin.clientside.shape.ShapeDynamic;

//math
import breslin.math.Vector3D;

/******************************************************
*				CLASS
********************************************************/
public class AbilityRotation extends Ability
{
public AbilityRotation(ShapeDynamic shapeDynamic)
{

}


/******************************************************
*				VARIABLES
********************************************************/
//AbilityRotationStateMachine mProcessTickStateMachine;
//AbilityRotationStateMachine mInterpolateTickStateMachine;

//shape
ShapeDynamic mShapeDynamic;

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
void processTick()
{

}
void interpolateTick(float renderTime)
{

}

//rotation
float getDegreesToServer()
{

	return 0;
}
void  calculateServerRotationSpeed()
{

}

}
