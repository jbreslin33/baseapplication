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

//vector
import com.jme3.math.Vector3f;

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
	System.out.println("STATE: ApplicationMain");
}

public void execute()
{
//System.out.println("execute main");	
        if (Keyboard.isKeyDown(Keyboard.KEY_G))
        {
System.out.println("GGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGG");
                mApplicationBreslin.mPlayingGame = true;

		mApplicationBreslin.mGame = new Game(mApplicationBreslin);
		
                
		Vector3f startCamPosition = new Vector3f(0, 20, 20);
                Vector3f lookAtVector     = new Vector3f(0,0,0);
                Vector3f worldDirection   = new Vector3f(0,1,0);
                mApplicationBreslin.getCamera().setLocation(startCamPosition);
                mApplicationBreslin.getCamera().lookAt(lookAtVector,worldDirection);
		mApplicationBreslin.mStateMachine.changeState(mApplicationBreslin.mApplicationPlay);
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
