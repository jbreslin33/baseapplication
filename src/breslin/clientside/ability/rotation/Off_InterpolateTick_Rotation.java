package breslin.clientside.ability.rotation;

/******************************************************
*				INCLUDES
********************************************************/
//parent
import breslin.clientside.ability.rotation.AbilityRotationState;

//shape
import breslin.clientside.shape.ShapeDynamic;
import breslin.clientside.shape.Shape;

//math
import breslin.math.Vector3D;

class Off_InterpolateTick_Rotation extends AbilityRotationState
{

	private static Off_InterpolateTick_Rotation mAbilityRotationState;

	/** A private Constructor prevents any other class from instantiating. */
	private Off_InterpolateTick_Rotation()
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

public static synchronized Off_InterpolateTick_Rotation getAbilityRotationState()
{
   	if (mAbilityRotationState == null){
    	mAbilityRotationState = new Off_InterpolateTick_Rotation();
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
	if (java.lang.Math.abs(abilityRotation.getDegreesToServer()) > abilityRotation.mRotInterpLimitLow)
    {
		abilityRotation.mInterpolateTickStateMachine.changeState(Normal_InterpolateTick_Rotation.getAbilityRotationState());
		return;
    }
}

public void exit(AbilityRotation abilityRotation)
{
}


}