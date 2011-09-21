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
//	System.out.println("i");
	Vector3D transVector = new Vector3D();

    transVector.x = abilityMove.mShapeDynamic.mCommandToRunOnShape.mMoveVelocity.x;
    transVector.y = abilityMove.mShapeDynamic.mCommandToRunOnShape.mMoveVelocity.y;
    transVector.z = abilityMove.mShapeDynamic.mCommandToRunOnShape.mMoveVelocity.z;

	transVector.x = transVector.x * abilityMove.mShapeDynamic.mGame.getRenderTime() * 1000;
	transVector.y = transVector.y * abilityMove.mShapeDynamic.mGame.getRenderTime() * 1000;
	transVector.z = transVector.z * abilityMove.mShapeDynamic.mGame.getRenderTime() * 1000;

	Vector3D newPosition = new Vector3D();
	newPosition.x = transVector.x + abilityMove.mShapeDynamic.getPosition().x;
	newPosition.y = transVector.y + abilityMove.mShapeDynamic.getPosition().y;
	newPosition.z = transVector.z + abilityMove.mShapeDynamic.getPosition().z;

	abilityMove.mShapeDynamic.setPosition(newPosition);

	//does this just prevent you from going below 0 up and down?
    if(abilityMove.mShapeDynamic.getPosition().y < 0.0)
	{
		abilityMove.mShapeDynamic.setPosition(abilityMove.mShapeDynamic.getPosition().x,
		0.0f,
		abilityMove.mShapeDynamic.getPosition().z);
	}
}

public void exit(AbilityMove abilityMove)
{
}


}