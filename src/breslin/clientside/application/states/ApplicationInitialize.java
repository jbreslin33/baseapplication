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
	System.out.println("Init:enter");
}

public void execute()
{
	System.out.println("Init:execute");
	//mApplicationBreslin.mSetup = true;
   // mApplicationBreslin.mStateMachine.changeState(mApplicationBreslin.mApplicationMain);
}

public void exit()
{
	System.out.println("Init:exit");
}

}
