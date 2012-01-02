package breslin.clientside.ability.move;

/******************************************************
*				INCLUDES
********************************************************/
//parent
import breslin.clientside.ability.move.AbilityMoveState;

//math
import breslin.math.Vector3D;

class Catchup_ProcessTick_Move extends AbilityMoveState
{

	private static Catchup_ProcessTick_Move mAbilityMoveState;

	/** A private Constructor prevents any other class from instantiating. */
	private Catchup_ProcessTick_Move()
	{
		  //	 Optional Code
	}

/******************************************************
*				METHODS
*
*
*
*
********************************************************/

public static synchronized Catchup_ProcessTick_Move getAbilityMoveState()
{
   	if (mAbilityMoveState == null){
    	mAbilityMoveState = new Catchup_ProcessTick_Move();
    }
	    return mAbilityMoveState;
}


public Object clone()throws CloneNotSupportedException
{
    throw new CloneNotSupportedException();
}



public void enter(AbilityMove abilityMove)
{
}

public void execute(AbilityMove abilityMove)
{
	//if we are back in sync
    if(abilityMove.mDeltaPosition <= abilityMove.mPosInterpLimitHigh || abilityMove.mShape.mServerCommandCurrent.mVelocity.isZero())
    {
		abilityMove.mProcessTickStateMachine.changeState(Normal_ProcessTick_Move.getAbilityMoveState());
    }
		//this is what we will set mCommandToRunOnShape.mMoveVelocity to
		Vector3D newVelocity = new Vector3D(); //vector to future server pos

		//first set newVelocity to most recent velocity from server.
 		newVelocity.copyValuesFrom(abilityMove.mShape.mServerCommandCurrent.mVelocity);

		//normalise it now we know what direction to head in.
        newVelocity.normalise();

		//le'ts find out how fast
		//change in position times our interp factor
        float multiplier = abilityMove.mDeltaPosition * abilityMove.mPosInterpFactor;

		//multiply our normalized velocity by multiplier(change * interpfactor)
		newVelocity.multiply(multiplier);

		//add the latest server position to our newvelocity
		newVelocity.add(abilityMove.mShape.mServerCommandCurrent.mPosition);

		//now subtract our current position from our new velocity
		newVelocity.subtract(abilityMove.mShape.getPosition());

        //dist from client pos to future server pos
        float predictDist = (float)
        (float)java.lang.Math.pow(newVelocity.x, 2) +
        (float)java.lang.Math.pow(newVelocity.y, 2) +
        (float)java.lang.Math.pow(newVelocity.z, 2);
        predictDist = (float)java.lang.Math.sqrt(predictDist);

        //server velocity
		if(abilityMove.mShape.mCommandToRunOnShape.mFrameTime != 0)
        {
			abilityMove.mShape.mSpeed = abilityMove.calcuateSpeed(
			abilityMove.mShape.mServerCommandCurrent.mVelocity,
			abilityMove.mShape.mCommandToRunOnShape.mFrameTime);

		}

		if(abilityMove.mShape.mSpeed != 0.0)
		{
			//time needed to get to future server pos
			float time = abilityMove.mDeltaPosition * abilityMove.mPosInterpFactor/abilityMove.mShape.mSpeed;

			newVelocity.normalise();  //?????what the hell why i am normalizing this after all that work above?

			//client vel needed to get to future server pos in time
			float distTime = predictDist/time;
			newVelocity.multiply(distTime);

			//set newVelocity to mCommandToRunOnShape.mMoveVelocity which is what interpolateTick uses
			//LogString("x:%f",newVelocity.x);

			//keep player from "teleporting"
			//abilityMove.regulate(newVelocity);

			abilityMove.mShape.mCommandToRunOnShape.mVelocity.copyValuesFrom(newVelocity);

		}
		else
		{
			//why would catchup ever need to set velocity to zero, wouldn't we simply leave catchup state??
			abilityMove.mShape.mCommandToRunOnShape.mVelocity.zero();

		}
}

public void exit(AbilityMove abilityMove)
{
}


}
