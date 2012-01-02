package breslin.clientside.ability.move;

/**********************************
*          INCLUDES
**********************************/
//math
import breslin.math.Vector3D;



/******************************************************
*				INCLUDES
********************************************************/
//parent
import breslin.clientside.ability.move.AbilityMoveState;


class Normal_ProcessTick_Move extends AbilityMoveState
{

	private static Normal_ProcessTick_Move mAbilityMoveState;

	/** A private Constructor prevents any other class from instantiating. */
	private Normal_ProcessTick_Move()
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

public static synchronized Normal_ProcessTick_Move getAbilityMoveState()
{
   	if (mAbilityMoveState == null){
    	mAbilityMoveState = new Normal_ProcessTick_Move();
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
	// if distance exceeds threshold && server velocity is zero
	if(abilityMove.mDeltaPosition > abilityMove.mPosInterpLimitHigh && !abilityMove.mShape.mServerCommandCurrent.mVelocity.isZero())
	{
		abilityMove.mProcessTickStateMachine.changeState(Catchup_ProcessTick_Move.getAbilityMoveState());
    }
		Vector3D serverVelocity = new Vector3D();
		serverVelocity.copyValuesFrom(abilityMove.mShape.mServerCommandCurrent.mVelocity);
		serverVelocity.normalise();

        if(abilityMove.mShape.mCommandToRunOnShape.mFrameTime != 0)
        {
			abilityMove.mShape.mSpeed = abilityMove.calcuateSpeed(
			abilityMove.mShape.mServerCommandCurrent.mVelocity,
			abilityMove.mShape.mCommandToRunOnShape.mFrameTime);
        }

		serverVelocity.multiply(abilityMove.mShape.mSpeed);

		//keep player from teleporting
		//abilityMove.regulate(serverDest);

		abilityMove.mShape.mCommandToRunOnShape.mVelocity.copyValuesFrom(serverVelocity);
}

public void exit(AbilityMove abilityMove)
{
}


}
