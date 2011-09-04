package breslin.clientside.ability.rotation;

/******************************************************
*				INCLUDES
********************************************************/
//parent
import breslin.clientside.ability.rotation.AbilityRotationState;


class Global_ProcessTick_Rotation extends AbilityRotationState
{

	private static Global_ProcessTick_Rotation singletonObject;

	/** A private Constructor prevents any other class from instantiating. */
	private Global_ProcessTick_Rotation()
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

public static synchronized Global_ProcessTick_Rotation getSingletonObject()
{
   	if (singletonObject == null){
    	singletonObject = new Global_ProcessTick_Rotation();
    }
	    return singletonObject;
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
	abilityRotation.calculateServerRotationSpeed();
	abilityRotation.mShapeDynamic.mGhost.yaw(abilityRotation.mServerRotSpeed,true);
}

public void exit(AbilityRotation abilityRotation)
{
}


}