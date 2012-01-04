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
	//user input
	mGame.processInput();

	//network outgoing
	mGame.sendByteBuffer();

	//network ingoing
	mGame.checkForByteBuffer();
}

public void exit()
{

}

}
