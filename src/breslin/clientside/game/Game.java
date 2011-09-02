package breslin.clientside.game;

/***************************************
*           INCLUDES
***************************************/
//standard library
import java.io.*;
import java.util.ArrayList;
import java.nio.ByteBuffer;

//dispatch
import breslin.clientside.bytebuffer.Dispatch;

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
*
*
*
*
***************************************/

/***************************************
*   		ADMIN
***************************************/
void shutdown()
{

}

/***************************************
*   		SHAPES
***************************************/
public void addShape(boolean b, ByteBuffer byteBuffer)
{

}

public void removeShape(ByteBuffer byteBuffer)
{

}

ShapeDynamic getShapeDynamic(int id)
{
	ByteBuffer byteBuffer = ByteBuffer.allocate(48);
	return new ShapeDynamic(this, byteBuffer);
}

/***************************************
*   		TICKS
***************************************/
public void readServerTick           (ByteBuffer byteBuffer)
{

}

void interpolateTick()
{

}

/***************************************
*   		TIME
***************************************/
float getRenderTime()
{
	return 0;
}

/***************************************
*   		NETWORK
***************************************/
public void runNetwork    (float msec)
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

/***************************************
*   		INPUT
***************************************/
void processInput()
{

}

/***************************************
*   		GRAPHICS
***************************************/
public boolean runGraphics()
{
	return false;
}


}