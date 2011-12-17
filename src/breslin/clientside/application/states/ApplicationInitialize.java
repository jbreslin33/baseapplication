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
	mApplicationBreslin.mSetup = true;
       	mApplicationBreslin.mStateMachine.changeState(mApplicationBreslin.mApplicationMain);
}

public void exit()
{

}

}
