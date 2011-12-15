package breslin.clientside.application.states;

/***************************************
*   		INCLUDES
***************************************/

//state machine
import breslin.statemachine.State;

//application
import breslin.clientside.application.ApplicationBreslin;

public class ApplicationPlay extends State
{

private ApplicationBreslin mApplicationBreslin;

public ApplicationPlay(ApplicationBreslin applicationBreslin)
{
	mApplicationBreslin = applicationBreslin;
}

public void enter()
{

}

public void execute()
{
	/*
	if (mApplicationBreslin.getKeyboard().isKeyDown(OIS::KC_ESCAPE))
	{
		mApplicationBreslin.mPlayingGame = false;
		mApplicationBreslin.mStateMachine.changeState(mApplicationBreslin.mApplicationMain);
	}
	else
	{
		//game
		mApplicationBreslin.mGame.processUpdate();
	}
	*/
}

public void exit()
{
	/*
	mApplicationBreslin.shutdown();

	mApplicationBreslin.getSceneManager().destroyAllEntities();
	delete mApplicationBreslin.mGame;

	mApplicationBreslin.showMainScreen();
	*/
}

}