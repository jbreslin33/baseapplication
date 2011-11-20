package breslin.clientside.ability.rotation;

/******************************************************
*				INCLUDES
********************************************************/
//parent
import breslin.clientside.ability.rotation.AbilityRotationState;

//shape
import breslin.clientside.shape.Shape;
import breslin.clientside.shape.Shape;

//math
import breslin.math.Vector3D;

class Normal_InterpolateTick_Rotation extends AbilityRotationState
{

	private static Normal_InterpolateTick_Rotation mAbilityRotationState;

	/** A private Constructor prevents any other class from instantiating. */
	private Normal_InterpolateTick_Rotation()
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

public static synchronized Normal_InterpolateTick_Rotation getAbilityRotationState()
{
   	if (mAbilityRotationState == null){
    	mAbilityRotationState = new Normal_InterpolateTick_Rotation();
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
	float rotSpeed = abilityRotation.mShape.mCommandToRunOnShape.mRotSpeed * abilityRotation.mShape.mGame.getRenderTime();
	abilityRotation.mShape.yaw(rotSpeed, true);

	if (abilityRotation.mServerRotSpeed == 0.0 && java.lang.Math.abs(abilityRotation.getDegreesToServer()) < abilityRotation.mRotInterpLimitLow)
    {
		abilityRotation.mInterpolateTickStateMachine.changeState(Off_InterpolateTick_Rotation.getAbilityRotationState());
		return;
    }
}

public void exit(AbilityRotation abilityRotation)
{
}


}