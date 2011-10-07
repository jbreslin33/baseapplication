package breslin.clientside.ability.rotation;

/******************************************************
*				INCLUDES
********************************************************/
//parent
import breslin.clientside.ability.rotation.AbilityRotationState;




class Global_ProcessTick_Rotation extends AbilityRotationState
{

	private static Global_ProcessTick_Rotation mAbilityRotationState;

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

public static synchronized Global_ProcessTick_Rotation getAbilityRotationState()
{
   	if (mAbilityRotationState == null){
    	mAbilityRotationState = new Global_ProcessTick_Rotation();
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
	abilityRotation.calculateServerRotationSpeed();
	System.out.println("GHOST:" + abilityRotation.mServerRotSpeed);
	abilityRotation.mShapeDynamic.mGhost.yaw(abilityRotation.mServerRotSpeed,true);
	//abilityRotation.mShapeDynamic.mGhost.yaw(abilityRotation.mShapeDynamic.mServerFrame.mRot.x,
	//abilityRotation.mShapeDynamic.mServerFrame.mRot.z);
}

public void exit(AbilityRotation abilityRotation)
{
}


}