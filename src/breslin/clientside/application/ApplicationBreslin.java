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

//parser
import breslin.clientside.parser.Parser;

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

public class ApplicationBreslin extends SimpleApplication
{

public ApplicationBreslin(byte[] serverIP, int serverPort)
{
	//network
	mNetwork = new Network(this,serverIP,serverPort);

	//time
	mFrameTime		 = 0.0f;

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

	//let their be light
	DirectionalLight directionalLight = new DirectionalLight();
	directionalLight.setDirection(new Vector3f(-0.1f, -1f, -1).normalizeLocal());
    getRootNode().addLight(directionalLight);

	mRenderTime = 0;
	mParser = new Parser();

	//sequences
	mOutgoingSequence		= 1;

	start();
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

//sequences
short	mOutgoingSequence;		// OutFgoing packet sequence

//initialize
boolean mInitializeGui;
boolean mJoinGame;
boolean mPlayingGame;

//game
Game mGame;

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

//key input
int mKeyCurrent;
int mKeyLast;

int mMillisecondsCurrent;
int mMillisecondsLast;

public float mFrameTime;
public float mRunNetworkTime;

//render time
public float mRenderTime;

Parser mParser;

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
	runNetwork(getRenderTime() * 1000.0f);

	//move objects
	mGame.run();

	//move objects
	interpolateTick();

	runGraphics();
}

//graphics
/* This is the update loop */
public void simpleUpdate(float tpf)
{
    mRenderTime = tpf;
}

void        createScene          ()
{

}

//boolean        frameRenderingQueued (const Ogre::FrameEvent& evt);

public boolean                runGraphics          ()
{
	//super and other stuff this is equivalent to c++ runGraphics...
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
	mNetwork.mCommandToServer.mKey = 0;

	if (Keyboard.isKeyDown(Keyboard.KEY_B))
	{
		if (!mPlayingGame)
		{
			mNetwork.sendConnect();
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
		mNetwork.mCommandToServer.mKey |= mKeyUp;
	}


	if (Keyboard.isKeyDown(Keyboard.KEY_K))
	{
		mNetwork.mCommandToServer.mKey |= mKeyDown;
	}


	if (Keyboard.isKeyDown(Keyboard.KEY_J))
	{
		mNetwork.mCommandToServer.mKey |= mKeyLeft;
	}


	if (Keyboard.isKeyDown(Keyboard.KEY_L))
	{
		mNetwork.mCommandToServer.mKey |= mKeyRight;
	}

	//rotation
	if (Keyboard.isKeyDown(Keyboard.KEY_G))
	{
		mNetwork.mCommandToServer.mKey |= mKeyCounterClockwise;
	}

	if (Keyboard.isKeyDown(Keyboard.KEY_H))
	{
		mNetwork.mCommandToServer.mKey |= mKeyClockwise;
	}

		mNetwork.mCommandToServer.mMilliseconds = (byte) (mFrameTime * 1000);
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
		shape = mGame.getShape(id);

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

	readPackets();

	// Framerate is too high
	if(mRunNetworkTime > (1000 / 60))
	{
		sendCommand();
		mFrameTime = mRunNetworkTime / 1000.0f;
		mRunNetworkTime = 0;
	}
}

public void shutdown()
{

}

public void readPackets()
{



	ByteBuffer byteBuffer = ByteBuffer.allocate(1400);
	while(mNetwork.checkForByteBuffer(byteBuffer))
	{

		byteBuffer.position(0); //BeginReading() c++ equivalent

		int type = byteBuffer.get();


		if (mParser.mMessageConnect == type)
		{
			System.out.println("BRESSAGE: mMessageConnect");
		}

		if (mParser.mMessageAddShape == type)
		{
			mGame.addShape(true,byteBuffer);
			System.out.println("BRESSAGE: mMessageAddShape");
		}

		if (mParser.mMessageRemoveShape == type)
		{
			mGame.removeShape(byteBuffer);
			System.out.println("BRESSAGE: mMessageRemoveShape");
		}

		if (mParser.mMessageFrame == type)
		{
			//System.out.println("BRESSAGE: mMessageFrame");
			readServerTick(byteBuffer);
		}

		if (mParser.mMessageServerExit == type)
		{
			//	mGame.shutdown();
		}
		byteBuffer.clear();
	}
}

public void sendCommand()
{
        //bools
        boolean sendKey          = false;
        boolean sendMilliseconds = false;

        //create byteBuffer
        byte[] mCharArray = new byte[1400];
        ByteBuffer byteBuffer = ByteBuffer.wrap(mCharArray);

        //WRITE: type
        byteBuffer.put(mParser.mMessageFrame);  //type

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
                flags |= mParser.mCommandKey;
        }


        if(mMillisecondsLast != mMillisecondsCurrent)
        {
                sendMilliseconds = true;

                flags |= mParser.mCommandMilliseconds;
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



};

