package breslin.clientside.application.states;

/***************************************
*   		INCLUDES
***************************************/

//state machine
import breslin.statemachine.State;

//application
import breslin.clientside.application.ApplicationBreslin;

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
	/*
	if (mApplicationBreslin.mButtonHit == mApplicationBreslin.mButtonGame)
	{
		mApplicationBreslin.mButtonHit = null;
		mApplicationBreslin.sendConnect();
		mApplicationBreslin.mGame = new Game(mApplicationBreslin);

		mApplicationBreslin.hideMainScreen();

		mApplicationBreslin.mStateMachine.changeState(mApplicationBreslin.mApplicationPlay);
	}

	if (mApplicationBreslin.mButtonHit == mApplicationBreslin.mButtonTag)
	{
		mApplicationBreslin.mButtonHit = null;
		mApplicationBreslin.sendConnect();
		mApplicationBreslin.mGame = new GameTag(mApplicationBreslin);

		mApplicationBreslin.hideMainScreen();

		mApplicationBreslin.mStateMachine.changeState(mApplicationBreslin.mApplicationPlay);
	}

	if (mApplicationBreslin.mButtonHit == mApplicationBreslin.mButtonExit)
	{

		mApplicationBreslin.mStateMachine.changeState(null);
		mApplicationBreslin.mStateMachine.setGlobalState(null);

		mApplicationBreslin.mButtonHit = null;

		mApplicationBreslin.shutdown();

		mApplicationBreslin.mShutDown = true;

		delete mApplicationBreslin;

	}
	*/
}

public void exit()
{

}

}