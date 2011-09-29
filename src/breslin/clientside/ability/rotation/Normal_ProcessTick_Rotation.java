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
	if(abilityMove.mDeltaPosition > abilityMove.mPosInterpLimitHigh && !abilityMove.mShapeDynamic.mServerFrame.mMoveVelocity.isZero())
	{

		abilityMove.mProcessTickStateMachine.changeState(Catchup_ProcessTick_Move.getAbilityMoveState());
    }
    else //server stopped or we are in sync so just use server vel as is..
    {
		Vector3D serverDest = new Vector3D();
		serverDest.copyValuesFrom(abilityMove.mShapeDynamic.mServerFrame.mMoveVelocity);
		serverDest.normalise();

        if(abilityMove.mShapeDynamic.mCommandToRunOnShape.mMilliseconds != 0)
        {
			abilityMove.mSpeed = abilityMove.calcuateSpeed(
			abilityMove.mShapeDynamic.mServerFrame.mMoveVelocity,
			abilityMove.mShapeDynamic.mCommandToRunOnShape.mMilliseconds);
        }

		serverDest.multiply(abilityMove.mSpeed);

		//keep player from teleporting
		abilityMove.regulate(serverDest);

		abilityMove.mShapeDynamic.mCommandToRunOnShape.mMoveVelocity.copyValuesFrom(serverDest);
	}
}

public void exit(AbilityMove abilityMove)
{
}


}