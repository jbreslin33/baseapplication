package breslin.clientside.game.states;

/***************************************
*   		INCLUDES
***************************************/

//state machine
import breslin.statemachine.State;

//game
import breslin.clientside.game.Game;

public class GamePlay extends State
{

private Game mGame;

public GamePlay(Game game)
{
	mGame = game;
}

public void enter()
{

}

public void execute()
{

	for (int i = 0; i < mGame.mShapeVector.size(); i++)
	{
		mGame.mShapeVector.get(i).interpolateTick(mGame.mApplicationBreslin.getRenderTime());
	}
}

public void exit()
{

}

}
