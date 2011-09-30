package breslin.clientside.game;

/***************************************
*   		INCLUDES
***************************************/
//standard library
import java.nio.ByteBuffer;

//graphics
import breslin.clientside.graphics.GraphicsMonkey;

//shape
import breslin.clientside.shape.ShapeDynamicMonkey;
import breslin.clientside.shape.ShapeDynamic;

//ability
//import breslin.clientside.ability.rotation.AbilityRotation;
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
	mRenderTime = 0;

	mGraphicsMonkey = new GraphicsMonkey(this);
}

/**************************************
*			MAIN
**************************************/
public static void main(String[] args)
{
	byte[] theByteArray;
	if (args.length > 0)
	{
		theByteArray = args[0].getBytes();
	}
	else
	{
		String s = "192.168.1.104";
		theByteArray = s.getBytes();
	}
	GameMonkey gameMonkey = new GameMonkey(theByteArray,30004);
}


/***************************************
*   		MEMBER VARIABLES
***************************************/

//graphics
public GraphicsMonkey mGraphicsMonkey;

//render time
public float mRenderTime;

/***************************************
*			          METHODS
***************************************/


//shape
public void addShape(boolean b, ByteBuffer byteBuffer)
{
	ShapeDynamic shapeDynamicMonkey = new ShapeDynamicMonkey(this,byteBuffer,false);  //you should just need to call this...

	//ability
	shapeDynamicMonkey.addAbility(new AbilityRotation(shapeDynamicMonkey));
	shapeDynamicMonkey.addAbility(new AbilityMove    (shapeDynamicMonkey));
}

//time
public float getRenderTime()
{
//	System.out.println("r:" + mRenderTime);
	return mRenderTime;
}


public boolean runGraphics()
{
	mGraphicsMonkey.runGraphics();
	return true;
}

void initializeGui()
{

}

void processInput()
{

}


}


