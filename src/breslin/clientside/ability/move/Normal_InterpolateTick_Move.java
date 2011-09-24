package breslin.clientside.ability.move;

/******************************************************
*				INCLUDES
********************************************************/
//parent
import breslin.clientside.ability.move.AbilityMoveState;

//shape
import breslin.clientside.shape.ShapeDynamic;
import breslin.clientside.shape.Shape;

//math
import breslin.math.Vector3D;

class Normal_InterpolateTick_Move extends AbilityMoveState
{

	private static Normal_InterpolateTick_Move mAbilityMoveState;

	/** A private Constructor prevents any other class from instantiating. */
	private Normal_InterpolateTick_Move()
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

public static synchronized Normal_InterpolateTick_Move getAbilityMoveState()
{
   	if (mAbilityMoveState == null){
    	mAbilityMoveState = new Normal_InterpolateTick_Move();
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
	//to be used to setPosition
	Vector3D transVector = new Vector3D();

	//copy values from mMoveVelocity so we don't make changes to original
  	transVector.copyValuesFrom(abilityMove.mShapeDynamic.mCommandToRunOnShape.mMoveVelocity);

	//get the mulitplier
	float multipliedRenderTime = abilityMove.mShapeDynamic.mGame.getRenderTime() * 1000;

	//multiply our vector using render values
	transVector.multiply(multipliedRenderTime);

	//add our velocity to current position
	transVector.add(abilityMove.mShapeDynamic.getPosition());

	//set new position
	abilityMove.mShapeDynamic.setPosition(transVector);
}

public void exit(AbilityMove abilityMove)
{
}


}