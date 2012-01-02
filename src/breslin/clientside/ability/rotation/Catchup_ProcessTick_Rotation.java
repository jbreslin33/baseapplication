package breslin.clientside.ability.rotation;

/******************************************************
*				INCLUDES
********************************************************/
//parent
import breslin.clientside.ability.rotation.AbilityRotationState;

//math
import breslin.math.Vector3D;

class Catchup_ProcessTick_Rotation extends AbilityRotationState
{

	private static Catchup_ProcessTick_Rotation mAbilityRotationState;

	/** A private Constructor prevents any other class from instantiating. */
	private Catchup_ProcessTick_Rotation()
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

public static synchronized Catchup_ProcessTick_Rotation getAbilityRotationState()
{
   	if (mAbilityRotationState == null){
    	mAbilityRotationState = new Catchup_ProcessTick_Rotation();
    }
	    return mAbilityRotationState;
}

public Object clone()throws CloneNotSupportedException
{
    throw new CloneNotSupportedException();
}

public void enter(AbilityRotation abilityRotation)
{
}

public void execute(AbilityRotation abilityRotation)
{
	// are we back on track
    if(java.lang.Math.abs(abilityRotation.mDegreesToServer) < abilityRotation.mRotInterpLimitLow)
    {
		abilityRotation.mProcessTickStateMachine.changeState(Normal_ProcessTick_Rotation.getAbilityRotationState());
		return;
    }
    else
    {
		if(abilityRotation.mServerRotSpeed != 0.0)
        {
			// if server rot counter-clockwise hardcode server rot to +mTurnSpeed
            if(abilityRotation.mServerRotSpeed > 0.0)
            {
				abilityRotation.mShape.mCommandToRunOnShape.mRotationSpeed = abilityRotation.mTurnSpeed;
            }
            else //clockwise - set to -mTurnSpeed
            {
				abilityRotation.mShape.mCommandToRunOnShape.mRotationSpeed = -abilityRotation.mTurnSpeed;
            }
			if(abilityRotation.mDegreesToServer / abilityRotation.mServerRotSpeed > 0.0)
            {
				abilityRotation.mShape.mCommandToRunOnShape.mRotationSpeed = abilityRotation.mShape.mCommandToRunOnShape.mRotationSpeed * abilityRotation.mRotInterpIncrease;
            }
            else
            {
				abilityRotation.mShape.mCommandToRunOnShape.mRotationSpeed = abilityRotation.mShape.mCommandToRunOnShape.mRotationSpeed * abilityRotation.mRotInterpDecrease;
            }
		}
        else if(abilityRotation.mServerRotSpeed == 0.0)
        {
			if (abilityRotation.mDegreesToServer > 0.0)
            {
				abilityRotation.mShape.mCommandToRunOnShape.mRotationSpeed = abilityRotation.mTurnSpeed;
            }
            else //clockwise - set to -mTurnSpeed
            {
				abilityRotation.mShape.mCommandToRunOnShape.mRotationSpeed = -abilityRotation.mTurnSpeed;
            }
		}
	}
}

public void exit(AbilityRotation abilityRotation)
{
}


}
