package breslin.clientside.application;

/***************************************
*   		INCLUDES
***************************************/

//parent
import com.jme3.app.
SimpleApplication;

//state machine
import breslin.statemachine.StateMachine;
import breslin.statemachine.State;

//states
import breslin.clientside.application.states.ApplicationGlobal;
import breslin.clientside.application.states.ApplicationInitialize;
import breslin.clientside.application.states.ApplicationMain;
import breslin.clientside.application.states.ApplicationPlay;

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

	//initilize
	mSetup = false;
	mPlayingGame = false;

	//time
	mRenderTime = 0.0f;

	//game
	mGame = null;

	//state machine (Menus)
	mStateMachine = new StateMachine();

	mApplicationGlobal = new ApplicationGlobal(this);
	mApplicationInitialize = new ApplicationInitialize(this);
	mApplicationMain   = new ApplicationMain  (this);
	mApplicationPlay   = new ApplicationPlay(this);

	mStateMachine.setGlobalState (mApplicationGlobal);
	//mStateMachine.changeState(mApplicationInitialize);
	mStateMachine.setPreviousState(mApplicationInitialize);
	mStateMachine.setCurrentState(mApplicationInitialize);
	System.out.println("end of constructor for ApplicationBreslin");
	//mApplicationInitialize.execute();

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
	while (true)
	{
		applicationBreslin.processUpdate();
	}
}

/***************************************
*   		MEMBER VARIABLES
***************************************/


//state machine
public StateMachine mStateMachine;

public State mApplicationGlobal;
public State mApplicationInitialize;
public State mApplicationMain;
public State mApplicationPlay;

//constants
public static final byte mMessageServerExit = 3;

public static final byte mMessageConnect     = -101;
public static final byte mMessageDisconnect  = -102;

//Network
public Network     mNetwork;

//game
public Game mGame;

//state transition variables
public boolean mSetup;
public boolean mPlayingGame;

//time
private float mRenderTime;


/***************************************
*	 METHODS
***************************************/

/*********************************
			update
**********************************/

public void processUpdate()
{
	//mStateMachine.update();
}

public void simpleUpdate(float tpf)
{
	mStateMachine.update();
    mRenderTime = tpf;
}

/***************************************
*	 ADMIN
***************************************/

public void shutdown()
{
	ByteBuffer byteBuffer = ByteBuffer.allocate(1400);
	byteBuffer.put(mMessageDisconnect);
	mNetwork.send(byteBuffer);
	mNetwork.reset();
}

/*********************************
		NETWORK
**********************************/

public void sendConnect()
{
	byte[] mCharArray = new byte[1400];
	ByteBuffer byteBuffer = ByteBuffer.wrap(mCharArray);

	byteBuffer.put(mMessageConnect);
	mNetwork.send(byteBuffer);
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
private void createMainScreen()
{
}

private void showMainScreen()
{
}

private void hideMainScreen()
{
}

/***************************************
*			CAMERA
******************************************/
public Vector3f getCameraLocation()
{
	return cam.getLocation();
}

public void processInput()
{
        if (Keyboard.isKeyDown(Keyboard.KEY_B))
        {
                sendConnect();
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

}