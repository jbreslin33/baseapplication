package breslin.clientside.application.states;

/***************************************
*   		INCLUDES
***************************************/

//state machine
import breslin.statemachine.State;

//application
import breslin.clientside.application.ApplicationBreslin;

//game
import breslin.clientside.game.Game;
//import breslin.clientside.game.GameTag;

//keyboard
import org.lwjgl.input.Keyboard;

public class ApplicationMain extends State
{

private ApplicationBreslin mApplicationBreslin;

public ApplicationMain(ApplicationBreslin applicationBreslin)
{
	mApplicationBreslin = applicationBreslin;
}

public void enter()
{
	//mApplicationBreslin.showMainScreen();
}

public void execute()
{
	
	if (Keyboard.isKeyDown(Keyboard.KEY_G))
	{
		mApplicationBreslin.sendConnect();
		mApplicationBreslin.mGame = new Game(mApplicationBreslin);

		mApplicationBreslin.mStateMachine.changeState(mApplicationBreslin.mApplicationPlay);
	}


	if (Keyboard.isKeyDown(Keyboard.KEY_T))
	{
/*
		mApplicationBreslin.sendConnect();
		mApplicationBreslin.mGame = new GameTag(mApplicationBreslin);

		mApplicationBreslin.mStateMachine.changeState(mApplicationBreslin.mApplicationPlay);
*/
	}

	if (Keyboard.isKeyDown(Keyboard.KEY_E))
	{

		mApplicationBreslin.mStateMachine.changeState(null);
		mApplicationBreslin.mStateMachine.setGlobalState(null);
		mApplicationBreslin.shutdown();

	}

}

public void exit()
{

}

}
