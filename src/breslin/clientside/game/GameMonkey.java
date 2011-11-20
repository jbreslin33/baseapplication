package breslin.clientside.game;

/***************************************
*   		INCLUDES
***************************************/
//standard library
import java.nio.ByteBuffer;

//graphics
import breslin.clientside.game.Application;



//ability
import breslin.clientside.ability.rotation.AbilityRotation;
import breslin.clientside.ability.move.AbilityMove;

/***************************************
*   		FORWARD DECLARATIONS
***************************************/

public class GameMonkey extends Game
{

public GameMonkey(byte[] serverIP, int serverPort)
{
	super(serverIP,serverPort);

	//time
	

	mApplication = new Application(this);
}




/***************************************
*   		MEMBER VARIABLES
***************************************/

//graphics
public Application mApplication;



/***************************************
*			          METHODS
***************************************/


//shape
public void addShape(boolean b, ByteBuffer byteBuffer)
{

}

//time





void initializeGui()
{

}

void processInput()
{

}


}


