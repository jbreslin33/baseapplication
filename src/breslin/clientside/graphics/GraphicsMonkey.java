package breslin.clientside.graphics;

/***************************************
*   		INCLUDES
***************************************/
//standard library
import com.jme3.math.Vector3f;

//lwgl
import org.lwjgl.LWJGLException;
import org.lwjgl.input.Keyboard;
import org.lwjgl.input.Mouse;
import org.lwjgl.opengl.Display;
import org.lwjgl.opengl.DisplayMode;

//parent
import com.jme3.app.SimpleApplication;

//game
import breslin.clientside.game.GameMonkey;

//input
import com.jme3.input.KeyInput;
import com.jme3.input.controls.ActionListener;
import com.jme3.input.controls.KeyTrigger;

//light
import com.jme3.light.DirectionalLight;


/***************************************
*   		FORWARD DECLARATIONS
***************************************/

public class GraphicsMonkey extends SimpleApplication
{

public GraphicsMonkey(GameMonkey gameMonkey)
{

	//game
	mGameMonkey = gameMonkey;

	//time
	mRenderTime = 0;

	//keys
	mKeyUp = 1;
	mKeyDown = 2;
	mKeyLeft = 4;
	mKeyRight = 8;
	mKeySpace = 16;

	//initilize
	mInitializeGui = false;
	mJoinGame    = false;
	mPlayingGame = false;

	start();

	//let their be light
	DirectionalLight directionalLight = new DirectionalLight();
	directionalLight.setDirection(new Vector3f(-0.1f, -1f, -1).normalizeLocal());
    getRootNode().addLight(directionalLight);

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

//time
float mRenderTime;

//gui
//OgreBites::Button* mJoinButton;

//keys
int mKeyUp;
int mKeyDown;
int mKeyLeft;
int mKeyRight;
int mKeySpace;

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
	mGameMonkey.runNetwork(1);

	//super and other stuff
	super.update();
}

void        createScene          ()
{

}

//boolean        frameRenderingQueued (const Ogre::FrameEvent& evt);

public boolean                runGraphics          ()
{
	System.out.println("running graphics");
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
//void buttonHit             (OgreBites::Button *button);
/*
void GraphicsOgre::buttonHit(OgreBites::Button *button)
{
	if (button == mJoinButton)
	{
		mJoinGame = true;
		if (mJoinGame && !mPlayingGame)
		{
			mGameOgre->mNetwork->sendConnect("myname");
			mPlayingGame = true;
		}

		hideGui();
	}
}
*/
//bool mouseMoved            ( const OIS::MouseEvent &arg );
void processInput()
{
	mGameMonkey.mNetwork.mCommandToServer.mKey = 0;

	if (Keyboard.isKeyDown(Keyboard.KEY_B))
	{
		if (!mPlayingGame)
		{
			System.out.println("send Connect.....");
			mGameMonkey.mNetwork.sendConnect();
			mPlayingGame = true;

			//Set Camera to position and to lookat avatar at 0,0,0
			Vector3f startCamPosition = new Vector3f(0, 20, 20);
			Vector3f lookAtVector = new Vector3f(0,0,0);
			Vector3f worldDirection   = new Vector3f(0,1,0);
			cam.setLocation(startCamPosition);
			System.out.println("setLocation of cam");
			cam.lookAt(lookAtVector,worldDirection);
		}
		else
		{
			System.out.println("slow your roll you already started");
		}
	}

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

	mGameMonkey.mNetwork.mCommandToServer.mMilliseconds = (int) (mGameMonkey.mFrameTime * 1000);
}




};

