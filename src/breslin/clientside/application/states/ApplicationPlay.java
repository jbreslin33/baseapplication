package breslin.clientside.application.states;

/***************************************
*   		INCLUDES
***************************************/

//state machine
import breslin.statemachine.State;

//application
import breslin.clientside.application.ApplicationBreslin;

//keyboard
import org.lwjgl.input.Keyboard;

public class ApplicationPlay extends State
{

private ApplicationBreslin mApplicationBreslin;

public ApplicationPlay(ApplicationBreslin applicationBreslin)
{
	mApplicationBreslin = applicationBreslin;
}

public void enter()
{
	System.out.println("Play:enter");
}

public void execute()
{
	System.out.println("Play:execute");
	if (Keyboard.isKeyDown(Keyboard.KEY_ESCAPE))
	{
		mApplicationBreslin.mPlayingGame = false;
		mApplicationBreslin.mStateMachine.changeState(mApplicationBreslin.mApplicationMain);
	}
	else
	{
		//game
		mApplicationBreslin.mGame.processUpdate();
	}
}

public void exit()
{
	System.out.println("Play:exit");
	mApplicationBreslin.shutdown();
}

}
