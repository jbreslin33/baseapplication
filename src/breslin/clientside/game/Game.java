package breslin.clientside.game;

/***************************************
*           INCLUDES
***************************************/
//standard library
import java.io.*;
import java.util.ArrayList;

//dispatch
import breslin.clientside.dispatch.Dispatch;

//shape
import breslin.clientside.shape.ShapeDynamic;

//network
import breslin.clientside.network.Network;

public class Game
{


public Game(byte[] serverIP, int serverPort)
{
	//StartLog();

	try
	{
		String serverIPString = new String(serverIP, "UTF8");
		System.out.println("serverIP:" + serverIPString + " serverPort:" + serverPort);

	}
	catch (UnsupportedEncodingException e)
	{
	    e.printStackTrace();
	}

	// network
	mNetwork = new Network(this,serverIP,serverPort);

	//time
	//mTime = new Time();
	mFrameTime		 = 0.0f;
	mOldTime         = 0;
}

/***************************************
*   		MEMBER VARIABLES
***************************************/
//Shapes
ArrayList<ShapeDynamic> mShapeVector = new ArrayList<ShapeDynamic>(); //all shapes in the client world
ArrayList<ShapeDynamic> mShapeGhostVector = new ArrayList<ShapeDynamic>(); //all shapes in the client world's ghost

//Network
public Network     mNetwork;

//time
//Time* mTime;
float mFrameTime;
float mRunNetworkTime;
int   mOldTime;


/***************************************
*			          METHODS
***************************************/

//Admin
void shutdown()
{

}
void gameLoop()
{
	while(true)
    {
		//input
		//processInput();  //right now

		//network
		runNetwork(getRenderTime() * 1000.0f);

		//move objects
		//interpolateTick();

		//draw
		//if (!runGraphics())
		//{
		//	break;
		//}
	}
}

//shape
public void         addShape       (boolean b, Dispatch dispatch)
{

}

void         removeShape    (Dispatch dispatch)
{

}

ShapeDynamic getShapeDynamic(int id)
{
	return new ShapeDynamic(this, new Dispatch());
}

//Ticks
void readServerTick           (Dispatch dispatch)
{

}

void interpolateTick()
{

}

//time
float getRenderTime()
{
	return 0;
}

// Network
void runNetwork    (float msec)
{
	mRunNetworkTime += msec;

	mNetwork.readPackets();

	// Framerate is too high
	if(mRunNetworkTime > (1000 / 60))
	{
	//	mNetwork.sendCommand();
		mFrameTime = mRunNetworkTime / 1000.0f;
		mRunNetworkTime = 0;
	}
}

//input
void processInput()
{

}

//graphics
boolean runGraphics()
{
	return false;
}


}