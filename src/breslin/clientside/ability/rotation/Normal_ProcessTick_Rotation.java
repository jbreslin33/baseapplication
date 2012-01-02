package breslin.clientside.ability.rotation;

/**********************************
*          INCLUDES
**********************************/
//math
import breslin.math.Vector3D;



/******************************************************
*				INCLUDES
********************************************************/
//parent
import breslin.clientside.ability.rotation.AbilityRotationState;


class Normal_ProcessTick_Rotation extends AbilityRotationState
{

	private static Normal_ProcessTick_Rotation mAbilityRotationState;

	/** A private Constructor prevents any other class from instantiating. */
	private Normal_ProcessTick_Rotation()
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

public static synchronized Normal_ProcessTick_Rotation getAbilityRotationState()
{
   	if (mAbilityRotationState == null){
    	mAbilityRotationState = new Normal_ProcessTick_Rotation();
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
	// are we too far off you need to change to catchup state

    if(java.lang.Math.abs(abilityRotation.mDegreesToServer) > abilityRotation.mRotInterpLimitHigh)
    {
		abilityRotation.mProcessTickStateMachine.changeState(Catchup_ProcessTick_Rotation.getAbilityRotationState());
		return;
    }
    else
    {

         if (abilityRotation.mServerRotSpeed == 0.0)
         {
			abilityRotation.mShape.mCommandToRunOnShape.mRotSpeed = 0.0f;
         }
         else
         {
			// if server rot counter-clockwise hardcode server rot to +mTurnSpeed
            if(abilityRotation.mServerRotSpeed > 0.0)
            {
				abilityRotation.mShape.mCommandToRunOnShape.mRotSpeed = abilityRotation.mTurnSpeed;
            }
			else //clockwise - set to -mTurnSpeed
            {
				abilityRotation.mShape.mCommandToRunOnShape.mRotSpeed = -abilityRotation.mTurnSpeed;
            }
		}
	}
}

public void exit(AbilityRotation abilityRotation)
{
}


}
