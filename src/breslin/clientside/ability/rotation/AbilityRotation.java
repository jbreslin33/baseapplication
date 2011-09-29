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
public void processTick()
{

}

public void interpolateTick(float renderTime)
{

}

//rotation
float getDegreesToServer()
{
	Vector3D serverRotNew = new Vector3D();

    serverRotNew.x = mShapeDynamic.mServerFrame.mRot.x;
	serverRotNew.y = 0;
    serverRotNew.z = mShapeDynamic.mServerFrame.mRot.z;

    serverRotNew.normalise();

    //calculate how far off we are from server
	float degreesToServer = mShapeDynamic.getDegreesToSomething(serverRotNew);

	return degreesToServer;
}
void  calculateServerRotationSpeed()
{
	mServerRotOld.zero();
    mServerRotNew.zero();

    mServerRotOld.x = mShapeDynamic.mServerFrame.mRotOld.x;
	mServerRotOld.y = 0;
    mServerRotOld.z = mShapeDynamic.mServerFrame.mRotOld.z;

    mServerRotNew.x = mShapeDynamic.mServerFrame.mRot.x;
	mServerRotNew.y = 0;
    mServerRotNew.z = mShapeDynamic.mServerFrame.mRot.z;

    mServerRotNew.normalise();
    mServerRotOld.normalise();

    //calculate how far off we are from server
	mDegreesToServer = mShapeDynamic.getDegreesToSomething(mServerRotNew);

    //calculate server rotation from last tick to new one
	mServerRotSpeed = mShapeDynamic.mGhost.getDegreesToSomething(mServerRotNew);

    if(java.lang.Math.abs(mServerRotSpeed) < 0)
    {
		mServerRotSpeed = 0.0f;
    }
}

}
