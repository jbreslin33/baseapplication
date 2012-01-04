package breslin.clientside.ability.rotation;

/******************************************************
*				INCLUDES
********************************************************/

//parent
import breslin.clientside.ability.Ability;

//state machines
import breslin.clientside.ability.rotation.AbilityRotationStateMachine;

//shapes
import breslin.clientside.shape.Shape;

//math
import breslin.math.Vector3D;



/******************************************************
*				CLASS
********************************************************/
public class AbilityRotation extends Ability
{
public AbilityRotation(Shape shape)
{
	mShape = shape;

	//Rotation processTick states
	mProcessTickStateMachine = new AbilityRotationStateMachine(this);    //setup the state machine
	mProcessTickStateMachine.setCurrentState      (Normal_ProcessTick_Rotation.getAbilityRotationState());
	mProcessTickStateMachine.setPreviousState     (Normal_ProcessTick_Rotation.getAbilityRotationState());
	mProcessTickStateMachine.setGlobalState       (Global_ProcessTick_Rotation.getAbilityRotationState());

	//Rotation interpolateTick states
	mInterpolateTickStateMachine = new AbilityRotationStateMachine(this);    //setup the state machine
	mInterpolateTickStateMachine.setCurrentState      (Normal_InterpolateTick_Rotation.getAbilityRotationState());
	mInterpolateTickStateMachine.setPreviousState     (Normal_InterpolateTick_Rotation.getAbilityRotationState());
	//mInterpolateTickStateMachine.setGlobalState       (null);

	//////rotation
    mTurnSpeed         = 250.0f;
    mServerRotSpeed    = 0.0f;
    mServerRotSpeedOld = 0.0f;
    mGhostSpeed        = 0.0f;

    mRotInterpLimitHigh = 6.0f; //how far away from server till we try to catch up
    mRotInterpLimitLow  = 4.0f; //how close to server till we are in sync
    mRotInterpIncrease  = 1.20f; //rot factor used to catchup to server
    mRotInterpDecrease  = 0.80f; //rot factor used to allow server to catchup to client

	//rotation
	mServerRotOld = new Vector3D();
	mServerRotNew = new Vector3D();
	mDegreesToServer = 0.0f;

}


/******************************************************
*				VARIABLES
********************************************************/
AbilityRotationStateMachine mProcessTickStateMachine;
AbilityRotationStateMachine mInterpolateTickStateMachine;

//shape
Shape mShape;

//rotation
float mTurnSpeed;
float mServerRotSpeed;
float mServerRotSpeedOld;
float mGhostSpeed;

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
	mProcessTickStateMachine.update();
}

public void interpolateTick(float renderTime)
{
	mInterpolateTickStateMachine.update();
}

//rotation
float getDegreesToServer()
{
	Vector3D serverRotNew = new Vector3D();

    serverRotNew.x = mShape.mServerCommandCurrent.mRotation.x;
	serverRotNew.y = 0;
    serverRotNew.z = mShape.mServerCommandCurrent.mRotation.z;

    serverRotNew.normalise();

    //calculate how far off we are from server
	float degreesToServer = mShape.getDegreesToSomething(serverRotNew);

	return degreesToServer;
}
void  calculateServerRotationSpeed()
{
	mServerRotOld.zero();
    mServerRotNew.zero();

    mServerRotOld.x = mShape.mServerCommandLast.mRotation.x;
	mServerRotOld.y = 0;
    mServerRotOld.z = mShape.mServerCommandLast.mRotation.z;

    mServerRotNew.x = mShape.mServerCommandCurrent.mRotation.x;
	mServerRotNew.y = 0;
    mServerRotNew.z = mShape.mServerCommandCurrent.mRotation.z;

    mServerRotNew.normalise();
    mServerRotOld.normalise();

    //calculate how far off we are from server
  	mDegreesToServer = mShape.getDegreesToSomething(mServerRotNew);

      //calculate server rotation from last tick to new one
  	mServerRotSpeedOld = mServerRotSpeed;

  	float serverRotSpeed = mShape.mGhost.getDegreesToSomething(mServerRotNew);
  	mGhostSpeed = serverRotSpeed;
  	//if it's a tiny value we have an anomoly which I have not solved yet so use mServerRotSpeedOld...
  	if (serverRotSpeed < 1.0f || serverRotSpeed > -1.0f)
  	{
  		mServerRotSpeed = mServerRotSpeedOld;
  	}
  	else
  	{
  		mServerRotSpeed = serverRotSpeed;
	}
}

}
