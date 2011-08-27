package breslin.clientside.game;

/***************************************
*   		INCLUDES
***************************************/
//standard library

//dispatch
import breslin.clientside.dispatch.Dispatch;

/***************************************
*   		FORWARD DECLARATIONS
***************************************/

public class GameMonkey extends Game
{

public GameMonkey(byte[] serverIP, int serverPort)
{
	super(serverIP,serverPort);
}


/***************************************
*   		MEMBER VARIABLES
***************************************/

//graphics
//GraphicsOgre mGraphicsOgre;

/***************************************
*			          METHODS
***************************************/

//shape
void addShape(boolean b, Dispatch dispatch)
{

}

//time
float getRenderTime()
{
	return 0;
}

//graphics
boolean runGraphics()
{
	return true;
}

void initializeGui()
{

}

void processInput()
{

}

}


