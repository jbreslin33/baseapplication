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
	//abilityMove.mShapeDynamic.appendToTitle("M:Normal");
//	System.out.println("M:Normal");
	// if distance exceeds threshold && server velocity is zero
	if(abilityMove.mDeltaPosition > abilityMove.mPosInterpLimitHigh && !abilityMove.mShapeDynamic.mServerFrame.mMoveVelocity.isZero())
	{
		abilityMove.mProcessTickStateMachine.changeState(Catchup_ProcessTick_Move.getAbilityMoveState());
    }
    else //server stopped or we are in sync so just use server vel as is..
    {

		Vector3D serverDest = new Vector3D();
		serverDest.x = abilityMove.mShapeDynamic.mServerFrame.mMoveVelocity.x;
	    serverDest.y = abilityMove.mShapeDynamic.mServerFrame.mMoveVelocity.y;
        serverDest.z = abilityMove.mShapeDynamic.mServerFrame.mMoveVelocity.z;
        serverDest.normalise();

        if(abilityMove.mShapeDynamic.mCommandToRunOnShape.mMilliseconds != 0)
        {

			abilityMove.mSpeed = (float)
			java.lang.Math.sqrt(
			java.lang.Math.pow(abilityMove.mShapeDynamic.mServerFrame.mMoveVelocity.x, 2) +
            java.lang.Math.pow(abilityMove.mShapeDynamic.mServerFrame.mMoveVelocity.y, 2) +
			java.lang.Math.pow(abilityMove.mShapeDynamic.mServerFrame.mMoveVelocity.z, 2)) /
			abilityMove.mShapeDynamic.mCommandToRunOnShape.mMilliseconds;
        }

        serverDest.x = serverDest.x * abilityMove.mSpeed;
        serverDest.y = serverDest.y * abilityMove.mSpeed;
        serverDest.z = serverDest.z * abilityMove.mSpeed;

		abilityMove.mShapeDynamic.mCommandToRunOnShape.mMoveVelocity.x = serverDest.x;
        abilityMove.mShapeDynamic.mCommandToRunOnShape.mMoveVelocity.y = serverDest.y;
        abilityMove.mShapeDynamic.mCommandToRunOnShape.mMoveVelocity.z = serverDest.z;
	}
}

public void exit(AbilityMove abilityMove)
{
}


}