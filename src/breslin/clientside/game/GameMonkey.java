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
	System.out.println("calling gameLoopFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF");
	gameLoop();

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

//render time
float mRenderTime;

/***************************************
*			          METHODS
***************************************/

//shape
public void addShape(boolean b, Dispatch dispatch)
{

}

//time
float getRenderTime()
{
	return mRenderTime;
}


//graphics
/* This is the update loop */
public void simpleUpdate(float tpf)
{
	// make the player rotate
    //player.rotate(0, 2*tpf, 0);
    mRenderTime = tpf;
}

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


