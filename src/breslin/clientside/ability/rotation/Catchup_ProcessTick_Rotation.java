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

}

public void exit(AbilityRotation abilityRotation)
{
}


}