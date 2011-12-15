package breslin.clientside.application.states;

/***************************************
*   		INCLUDES
***************************************/

//state machine
import breslin.statemachine.State;

//application
import breslin.clientside.application.ApplicationBreslin;

public class ApplicationInitialize extends State
{

private ApplicationBreslin mApplicationBreslin;

public ApplicationInitialize(ApplicationBreslin applicationBreslin)
{
	mApplicationBreslin = applicationBreslin;
}

public void enter()
{

}

public void execute()
{
	/*
	//setup calls ogre specific graphics setup,
	//when it returns true we can begin our graphics stuff
	if (mApplicationBreslin.setup())
	{
		mApplicationBreslin.mSetup = true;
		mApplicationBreslin.createMainScreen();
        	mApplicationBreslin.mStateMachine.changeState(mApplicationBreslin.mApplicationMain);
	}
	*/
}

public void exit()
{

}

}