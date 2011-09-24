package breslin.clientside.ability.move;

/******************************************************
*				INCLUDES
********************************************************/

//parent
import breslin.clientside.ability.Ability;

//state machines
import breslin.clientside.ability.move.AbilityMoveStateMachine;

//shapes
import breslin.clientside.shape.ShapeDynamic;

//math
import breslin.math.Vector3D;
import java.lang.Math;


/******************************************************
*				CLASS
********************************************************/
public class AbilityMove extends Ability
{
public AbilityMove(ShapeDynamic shapeDynamic)
{
	mShapeDynamic = shapeDynamic;

	//move processTick states
	mProcessTickStateMachine = new AbilityMoveStateMachine(this);    //setup the state machine
	mProcessTickStateMachine.setCurrentState      (Normal_ProcessTick_Move.getAbilityMoveState());
	mProcessTickStateMachine.setPreviousState     (Normal_ProcessTick_Move.getAbilityMoveState());
	mProcessTickStateMachine.setGlobalState       (Global_ProcessTick_Move.getAbilityMoveState());

	//move interpolateTick states
	mInterpolateTickStateMachine = new AbilityMoveStateMachine(this);    //setup the state machine
	mInterpolateTickStateMachine.setCurrentState      (Normal_InterpolateTick_Move.getAbilityMoveState());
	mInterpolateTickStateMachine.setPreviousState     (Normal_InterpolateTick_Move.getAbilityMoveState());
	mInterpolateTickStateMachine.setGlobalState       (null);

	//speed
	mSpeed     = 0.0f;

    //thresholds
    mPosInterpLimitHigh = .066f; //how far away from server till we try to catch up
    mPosInterpFactor    = 4.0f;
   	mMaximunVelocity    = .002083f; //do not let velocity go above this in any direction.

	//deltas
	mDeltaX        = 0.0f;
	mDeltaY		   = 0.0f;
	mDeltaZ        = 0.0f;
	mDeltaPosition = 0.0f;
}

/******************************************************
*				VARIABLES
********************************************************/
//shapeDynamic
ShapeDynamic mShapeDynamic;

//state machines
AbilityMoveStateMachine mProcessTickStateMachine;
AbilityMoveStateMachine mInterpolateTickStateMachine;

//speed
public float mSpeed;

//thresholds
public float mPosInterpLimitHigh;
public float mPosInterpFactor;
public float mMaximunVelocity;

//deltas
public float mDeltaX;
public float mDeltaZ;
public float mDeltaY;
public float mDeltaPosition;

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

/******************************************************
*				MOVE
********************************************************/

void calculateDeltaPosition()  //mov
{

	mDeltaX = mShapeDynamic.mServerFrame.mPosition.x - mShapeDynamic.getPosition().x;
    mDeltaY = mShapeDynamic.mServerFrame.mPosition.y - mShapeDynamic.getPosition().y;
    mDeltaZ = mShapeDynamic.mServerFrame.mPosition.z - mShapeDynamic.getPosition().z;

    //distance we are off from server
    mDeltaPosition = (float)java.lang.Math.sqrt(
		java.lang.Math.pow((double)mDeltaX, 2.0) +
    	java.lang.Math.pow((double)mDeltaY, 2.0) +
    	java.lang.Math.pow((double)mDeltaZ, 2.0));
}


float calcuateSpeed(Vector3D velocity, int milliseconds)
{
	float speed = (float)java.lang.Math.sqrt(
	java.lang.Math.pow(velocity.x, 2) +
    java.lang.Math.pow(velocity.y, 2) +
	java.lang.Math.pow(velocity.z, 2)) /
	milliseconds;

	return speed;
}

void regulate(Vector3D velocityToRegulate)
{
	if (velocityToRegulate.x > mMaximunVelocity)
	{
		System.out.println("x:" + velocityToRegulate.x);
		velocityToRegulate.x = mMaximunVelocity;
	}

	if (velocityToRegulate.x < mMaximunVelocity * -1)
	{
		System.out.println("x:" + velocityToRegulate.x);
		velocityToRegulate.x = mMaximunVelocity * -1;
	}

	if (velocityToRegulate.y > mMaximunVelocity)
	{
		System.out.println("y:" + velocityToRegulate.y);
		velocityToRegulate.y = mMaximunVelocity;
	}

	if (velocityToRegulate.y < mMaximunVelocity * -1)
	{
		System.out.println("y:" + velocityToRegulate.y);
		velocityToRegulate.y = mMaximunVelocity * -1;
	}
}

};