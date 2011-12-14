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

class StateMachine
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
void setGlobalState(State s)
{
	mGlobalState = s;
}
void setPreviousState(State s)
{
	mPreviousState = s;
}

void  update()
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

void  changeState(State pNewState)
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


