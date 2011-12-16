package breslin.statemachine;

/*
          INCLUDES
*/

/*
          FORWARD DECLARATIONS
*/


/*
          CLASS
*/

public class StateMachine
{

public StateMachine()
{

}

/*
          VARIABLES
*/
private State mCurrentState;
private State mPreviousState;
private State mGlobalState;

/*
          METHODS
*/
public void setCurrentState(State s)
{
	mCurrentState = s;
}

public void setGlobalState(State s)
{
	mGlobalState = s;
}

public void setPreviousState(State s)
{
	mPreviousState = s;
}

public void  update()
{
	if(mGlobalState != null)
	{
		mGlobalState.execute();
	}
	if (mCurrentState != null)
	{
		mCurrentState.execute();
	}
 }

public void  changeState(State pNewState)
{
	mPreviousState = mCurrentState;

	if(mCurrentState != null)
	{
       	mCurrentState.exit();
	}

    mCurrentState = pNewState;

	if(mCurrentState != null)
	{
        mCurrentState.enter();
	}
}

}


