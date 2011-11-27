package breslin.clientside.application;

/***************************************
*   		INCLUDES
***************************************/

//parent
import com.jme3.app.SimpleApplication;

//game
import breslin.clientside.game.Game;

//network
import breslin.clientside.network.Network;


//shape
import breslin.clientside.shape.Shape;

//standard library
import com.jme3.math.Vector3f;


//parent
import com.jme3.app.SimpleApplication;

//lwgl
import org.lwjgl.LWJGLException;
import org.lwjgl.input.Keyboard;
import org.lwjgl.input.Mouse;
import org.lwjgl.opengl.Display;
import org.lwjgl.opengl.DisplayMode;

//input
import com.jme3.input.KeyInput;
import com.jme3.input.controls.ActionListener;
import com.jme3.input.controls.KeyTrigger;

//light
import com.jme3.light.DirectionalLight;
import com.jme3.light.AmbientLight;
import com.jme3.light.PointLight;
//import com.jme3.light.SpotLight;

//color
import com.jme3.math.ColorRGBA;

import java.nio.ByteBuffer;


import java.io.UnsupportedEncodingException;

//tut
 
import com.jme3.font.BitmapText;
import com.jme3.material.Material;
import com.jme3.math.Vector3f;
import com.jme3.scene.Geometry;
import com.jme3.scene.Spatial;
import com.jme3.scene.shape.Box;

/***************************************
*   		FORWARD DECLARATIONS
***************************************/

public class ApplicationBreslin extends SimpleApplication
{

public ApplicationBreslin(byte[] serverIP, int serverPort)
{
	start();
	
	//network
	mNetwork = new Network(this,serverIP,serverPort);

	//time
	mFrameTime  = 0.0f;
	mRenderTime = 0.0f;
	mRunNetworkTime = 0.0f;	

	//keys
	mKeyUp = 1;
	mKeyDown = 2;
	mKeyLeft = 4;
	mKeyRight = 8;
	mKeyCounterClockwise = 16;
	mKeyClockwise = 32;

	//initilize
	mInitializeGui = false;
	mJoinGame    = false;
	mPlayingGame = false;

	//game
	mGame = new Game(this);

	//input
	mKeyCurrent = 0;
	mKeyLast = 0;
	mMillisecondsCurrent = 0;
	mMillisecondsLast = 0;

	//sequences
	mOutgoingSequence		= 1;

	
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
	ApplicationBreslin applicationBreslin = new ApplicationBreslin(theByteArray,30004);
}

/***************************************
*   		MEMBER VARIABLES
***************************************/

//constants
public static final byte mCommandMilliseconds = 2;

private static final byte mCommandKey          = 1;

private static final byte mMessageFrame = 1;

private static final byte mMessageConnect     = -101;
private static final byte mMessageDisconnect  = -102;
private static final byte mMessageAddShape    = -103;
private static final byte mMessageRemoveShape = -104;

private static final byte mMessageServerExit = 3;
private static final byte mMessageKeepAlive = 12;


//Network
private Network     mNetwork;

//game
private Game mGame;

//sequences
private short	mOutgoingSequence;		// OutFgoing packet sequence

//time
private float mFrameTime;
private float mRenderTime; 
private float mRunNetworkTime;

//initialize
private boolean mInitializeGui;
private boolean mJoinGame;
private boolean mPlayingGame;

//keys
private int mKeyUp;
private int mKeyDown;
private int mKeyLeft;
private int mKeyRight;
private int mKeyCounterClockwise;
private int mKeyClockwise;

//key input
private int mKeyCurrent;
private int mKeyLast;
private int mMillisecondsCurrent;
private int mMillisecondsLast;


/***************************************
*	 METHODS
***************************************/

/***************************************
*	 LOOP
***************************************/

public void update()
{

	//input
	processInput();

	//network
	runNetwork(getRenderTime() * 1000.0f);

	//move objects
	mGame.run();
	
	//graphics
	runGraphics();
}

/* This is the update loop */
public void simpleUpdate(float tpf)
{
    mRenderTime = tpf;
}

/***************************************
*	 ADMIN
***************************************/

private void shutdown()
{
	ByteBuffer byteBuffer = ByteBuffer.allocate(1400);
	byteBuffer.put(mMessageDisconnect);
	mNetwork.send(byteBuffer);
	mNetwork.reset();
}


/***************************************
*   		NETWORK
***************************************/
private void runNetwork(float msec)
{
	mRunNetworkTime += msec;

	readPackets();

	// Framerate is too high
	if(mRunNetworkTime > (1000 / 60))
	{
		sendCommand();
		mFrameTime = mRunNetworkTime / 1000.0f;
		mRunNetworkTime = 0.0f;
	}
}

private void readPackets()
{

	int type = 0;
	
	ByteBuffer byteBuffer = ByteBuffer.allocate(1400);

	while(mNetwork.checkForByteBuffer(byteBuffer))
	{

		byteBuffer.position(0); //BeginReading() c++ equivalent

		type = byteBuffer.get();


		if (mMessageConnect == type)
		{
			System.out.println("BRESSAGE: mMessageConnect");
		}

		if (mMessageAddShape == type)
		{
			mGame.addShape(true,byteBuffer);
			System.out.println("BRESSAGE: mMessageAddShape");
		}

		if (mMessageRemoveShape == type)
		{
			mGame.removeShape(byteBuffer);
			System.out.println("BRESSAGE: mMessageRemoveShape");
		}

		if (mMessageFrame == type)
		{
			readServerTick(byteBuffer);
		}

		if (mMessageServerExit == type)
		{
			//	mGame.shutdown();
		}
		byteBuffer.clear();
	}
}

private void sendCommand()
{
        //bools
        boolean sendKey          = false;
        boolean sendMilliseconds = false;

        //create byteBuffer
        byte[] mCharArray = new byte[1400];
        ByteBuffer byteBuffer = ByteBuffer.wrap(mCharArray);

        //WRITE: type
        byteBuffer.put(mMessageFrame);  //type

        //WRITE: sequence
        byteBuffer.putShort(mOutgoingSequence);  //sequence
        mOutgoingSequence++; //increase for next time...

        byte one = byteBuffer.get(1);
        byte two = byteBuffer.get(2);
        byteBuffer.put(1,two);
        byteBuffer.put(2,one);

        // Build delta-compressed move command
        int flags = 0;

        // Check what needs to be updated
        if(mKeyLast != mKeyCurrent)
        {
                sendKey = true;
                flags |= mCommandKey;
        }


        if(mMillisecondsLast != mMillisecondsCurrent)
        {
                sendMilliseconds = true;

                flags |= mCommandMilliseconds;
        }


        // Add to the message
        byteBuffer.put((byte)flags);

        if (sendKey)
        {
                byteBuffer.put((byte)mKeyCurrent);
        }

        if (sendMilliseconds)
        {

                byteBuffer.put((byte)mMillisecondsCurrent);
        }

        //set 'last' commands for diff
        mKeyLast = mKeyCurrent;
        mMillisecondsLast = mMillisecondsCurrent;

        // Send the packet
        mNetwork.send(byteBuffer);
}


private void sendConnect()
{
	byte[] mCharArray = new byte[1400];
	ByteBuffer byteBuffer = ByteBuffer.wrap(mCharArray);

	byteBuffer.put(mMessageConnect);
	mNetwork.send(byteBuffer);
}


private void readServerTick(ByteBuffer byteBuffer)
{
	
	// Skip sequences
	byte one = byteBuffer.get(1);
	byte two = byteBuffer.get(2);
	byteBuffer.put(1,two);
	byteBuffer.put(2,one);
	byteBuffer.position(1);
	short sequence = byteBuffer.getShort();

	int id = byteBuffer.get();
	//System.out.println("id:" + id);


	//while (byteBuffer.hasRemaining())
	//{

		//mDetailsPanel->setParamValue(11, Ogre::StringConverter::toString(byteBuffer->GetSize()));

		//int id = byteBuffer.get();
		//System.out.println("id:" + id);

		Shape shape = null;
		shape = mGame.getShape(id);

		if (shape != null)
		{
			//System.out.println("got shape");
			shape.processDeltaByteBuffer(byteBuffer);
			
		}

	//}

}

/*********************************
		TIME
**********************************/

public float getRenderTime()
{
	return mRenderTime;
}

/*********************************
		GRAPHICS
**********************************/

public void simpleInitApp()
{
        DirectionalLight directionalLight = new DirectionalLight();
        directionalLight.setDirection(new Vector3f(-0.1f, -1f, -1).normalizeLocal());
	getRootNode().addLight(directionalLight);
}

private boolean runGraphics()
{
	//super and other stuff this is equivalent to c++ runGraphics...
	super.update();

	return true;
}

/*********************************
		GUI
**********************************/
private void initializeGui()
{

}

private void loadJoinScreen()
{

}

private void hideGui()
{

}

private void hideJoinScreen()
{

}

/***************************************
*			INPUT
******************************************/
private void processInput()
{
	mKeyCurrent = 0;

	if (Keyboard.isKeyDown(Keyboard.KEY_B))
	{
		if (!mPlayingGame)
		{

			sendConnect();
			mPlayingGame = true;

			//Set Camera to position and to lookat avatar at 0,0,0(this should be same as ogre! if not fix it)
			Vector3f startCamPosition = new Vector3f(0, 20, 20);
			Vector3f lookAtVector     = new Vector3f(0,0,0);
			Vector3f worldDirection   = new Vector3f(0,1,0);
			cam.setLocation(startCamPosition);
			cam.lookAt(lookAtVector,worldDirection);
			System.out.println("Camera is setCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC");

		}
		else
		{
			System.out.println("slow your roll you already started");
		}
	}

	//move
	if (Keyboard.isKeyDown(Keyboard.KEY_I))
	{
		mKeyCurrent |= mKeyUp;
	}


	if (Keyboard.isKeyDown(Keyboard.KEY_K))
	{
		mKeyCurrent |= mKeyDown;
	}


	if (Keyboard.isKeyDown(Keyboard.KEY_J))
	{
		mKeyCurrent |= mKeyLeft;
	}


	if (Keyboard.isKeyDown(Keyboard.KEY_L))
	{
		mKeyCurrent |= mKeyRight;
	}

	//rotation
	if (Keyboard.isKeyDown(Keyboard.KEY_G))
	{
		mKeyCurrent |= mKeyCounterClockwise;
	}

	if (Keyboard.isKeyDown(Keyboard.KEY_H))
	{
		mKeyCurrent |= mKeyClockwise;
	}

		mMillisecondsCurrent = (byte) (mFrameTime * 1000);
}

/***************************************
*			CAMERA
******************************************/
public Vector3f getCameraLocation()
{
	return cam.getLocation();
}





};

