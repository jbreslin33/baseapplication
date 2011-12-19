package breslin.clientside.application.states;

/***************************************
*   		INCLUDES
***************************************/

//state machine
import breslin.statemachine.State;

//application
import breslin.clientside.application.ApplicationBreslin;

public class ApplicationGlobal extends State
{

private ApplicationBreslin mApplicationBreslin;

public ApplicationGlobal(ApplicationBreslin applicationBreslin)
{
	mApplicationBreslin = applicationBreslin;
}

public void enter()
{
	System.out.println("Global:enter");
}

public void execute()
{
	System.out.println("Global:execute");
	if (mApplicationBreslin.mSetup)
	{
		//graphics
//		mApplicationBreslin.runGraphics();
	}
}

public void exit()
{
	System.out.println("Global:exit");
}

}
