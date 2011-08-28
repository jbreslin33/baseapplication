package breslin.clientside.game;

/***************************************
*   		INCLUDES
***************************************/
//standard library

//dispatch
import breslin.clientside.dispatch.Dispatch;

//graphics
import breslin.clientside.graphics.GraphicsMonkey;

/***************************************
*   		FORWARD DECLARATIONS
***************************************/

public class GameMonkey extends Game
{

public GameMonkey(byte[] serverIP, int serverPort)
{
	super(serverIP,serverPort);
	mGraphicsMonkey = new GraphicsMonkey(this);

}

/**************************************
*			MAIN
**************************************/
public static void main(String[] args)
{
	byte[] theByteArray = args[0].getBytes();
	GameMonkey gameMonkey = new GameMonkey(theByteArray,30004);
   // gameMonkey.start();
}


/***************************************
*   		MEMBER VARIABLES
***************************************/

//graphics
GraphicsMonkey mGraphicsMonkey;

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


