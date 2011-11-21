package breslin.clientside.game;

/***************************************
*   		INCLUDES
***************************************/

//parent
import com.jme3.app.SimpleApplication;

//game
import breslin.clientside.game.GameMonkey;

//network
import breslin.clientside.network.Network;

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


import java.nio.ByteBuffer;


import java.io.UnsupportedEncodingException;

/***************************************
*   		FORWARD DECLARATIONS
***************************************/

public class Application extends SimpleApplication
{

public Application(byte[] serverIP, int serverPort)
{
//from game
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


	//game
	mGameMonkey = gameMonkey;

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

	start();

	//let their be light
	DirectionalLight directionalLight = new DirectionalLight();
	directionalLight.setDirection(new Vector3f(-0.1f, -1f, -1).normalizeLocal());
    getRootNode().addLight(directionalLight);

mRenderTime = 0;

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
	Application application = new Application(theByteArray,30004);
}

/***************************************
*   		MEMBER VARIABLES
***************************************/

//initialize
boolean mInitializeGui;
boolean mJoinGame;
boolean mPlayingGame;

//game
GameMonkey mGameMonkey;

//Network
public Network     mNetwork;

//gui
//OgreBites::Button* mJoinButton;

//keys
int mKeyUp;
int mKeyDown;
int mKeyLeft;
int mKeyRight;
int mKeySpace;

int mKeyCounterClockwise;
int mKeyClockwise;

public float mFrameTime;
public float mRunNetworkTime;
public int   mOldTime;

//render time
public float mRenderTime;

/***************************************
*			          METHODS
***************************************/

public void simpleInitApp()
{

}

public void update()
{
	//input
	processInput();

	//network
	mGameMonkey.runNetwork(getRenderTime() * 1000.0f);

	//move objects
	mGameMonkey.interpolateTick();

	//super and other stuff
	super.update();
}

//graphics
/* This is the update loop */
public void simpleUpdate(float tpf)
{
    mGameMonkey.mRenderTime = tpf;
}

void        createScene          ()
{

}

//boolean        frameRenderingQueued (const Ogre::FrameEvent& evt);

public boolean                runGraphics          ()
{
	super.update();
	return true;
}

//gui
void hideGui()
{

}

void loadJoinScreen()
{

}

void hideJoinScreen()
{

}
void unloadOtherScreens()
{

}
void initializeGui()
{

}

//input
void processInput()
{
	mGameMonkey.mNetwork.mCommandToServer.mKey = 0;

	if (Keyboard.isKeyDown(Keyboard.KEY_B))
	{
		if (!mPlayingGame)
		{
			mGameMonkey.mNetwork.sendConnect();
			mPlayingGame = true;

			//Set Camera to position and to lookat avatar at 0,0,0(this should be same as ogre! if not fix it)
			Vector3f startCamPosition = new Vector3f(0, 20, 20);
			Vector3f lookAtVector     = new Vector3f(0,0,0);
			Vector3f worldDirection   = new Vector3f(0,1,0);
			cam.setLocation(startCamPosition);
			cam.lookAt(lookAtVector,worldDirection);
		}
		else
		{
			System.out.println("slow your roll you already started");
		}
	}

	//move
	if (Keyboard.isKeyDown(Keyboard.KEY_I))
	{
		mGameMonkey.mNetwork.mCommandToServer.mKey |= mKeyUp;
	}


	if (Keyboard.isKeyDown(Keyboard.KEY_K))
	{
		mGameMonkey.mNetwork.mCommandToServer.mKey |= mKeyDown;
	}


	if (Keyboard.isKeyDown(Keyboard.KEY_J))
	{
		mGameMonkey.mNetwork.mCommandToServer.mKey |= mKeyLeft;
	}


	if (Keyboard.isKeyDown(Keyboard.KEY_L))
	{
		mGameMonkey.mNetwork.mCommandToServer.mKey |= mKeyRight;
	}

	//rotation
	if (Keyboard.isKeyDown(Keyboard.KEY_G))
	{
		mGameMonkey.mNetwork.mCommandToServer.mKey |= mKeyCounterClockwise;
	}

	if (Keyboard.isKeyDown(Keyboard.KEY_H))
	{
		mGameMonkey.mNetwork.mCommandToServer.mKey |= mKeyClockwise;
	}

	mGameMonkey.mNetwork.mCommandToServer.mMilliseconds = (byte) (mGameMonkey.mFrameTime * 1000);
}


public Vector3f getCameraLocation()
{
	return cam.getLocation();
}

public float getRenderTime()
{
//	System.out.println("r:" + mRenderTime);
	return mRenderTime;
}

/***************************************
*   		TICKS
***************************************/
public void readServerTick           (ByteBuffer byteBuffer)
{
	// Skip sequences
	//short sequence = byteBuffer.get();

	//WRITE: sequence
	//byteBuffer.putShort(mOutgoingSequence);  //sequence
	byte one = byteBuffer.get(1);
	byte two = byteBuffer.get(2);
	byteBuffer.put(1,two);
	byteBuffer.put(2,one);
	byteBuffer.position(1);
	short sequence = byteBuffer.getShort();
//	System.out.println("sequence:" + sequence);





	while (byteBuffer.hasRemaining())
	{

		//mDetailsPanel->setParamValue(11, Ogre::StringConverter::toString(byteBuffer->GetSize()));

		int id = byteBuffer.get();
		//System.out.println("id:" + id);

		Shape shape = null;
		shape = getShape(id);

		if (shape != null)
		{
			//System.out.println("got shape");
			shape.readDeltaMoveCommand(byteBuffer);
		}

	}

}


public void interpolateTick()
{



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
		mNetwork.sendCommand();
		mFrameTime = mRunNetworkTime / 1000.0f;
		mRunNetworkTime = 0;
	}
}

public void shutdown()
{

}

};

