package breslin.clientside.ability.move;

/******************************************************
*				INCLUDES
********************************************************/
//parent
import breslin.clientside.ability.move.AbilityMoveState;


class Global_ProcessTick_Move extends AbilityMoveState
{

	private static Global_ProcessTick_Move mAbilityMoveState;

	/** A private Constructor prevents any other class from instantiating. */
	private Global_ProcessTick_Move()
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

public static synchronized Global_ProcessTick_Move getAbilityMoveState()
{
   	if (mAbilityMoveState == null){
    	mAbilityMoveState = new Global_ProcessTick_Move();
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
	abilityMove.mShape.moveGhostShape();
	abilityMove.calculateDeltaPosition();
}

public void exit(AbilityMove abilityMove)
{
}


}