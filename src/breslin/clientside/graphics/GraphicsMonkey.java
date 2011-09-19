package breslin.clientside.graphics;

/***************************************
*   		INCLUDES
***************************************/
//standard library
import com.jme3.math.Vector3f;

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
	System.out.println("hereddddddddddddddddddddddddddddddddd");

	//for (int i = 0; i < 256; i++)
	//{
	//	keyBuffer[i] = false;
	//}

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

boolean[] keyBuffer;



/***************************************
*			          METHODS
***************************************/

public void update()
{
	mGameMonkey.runNetwork(1);
	super.update();
}



public void simpleInitApp()
{
	System.out.println("initialize keys with initKeys");
    initKeys(); // load my custom keybinding
}

//input
private void initKeys()
{

	/**********Join******/

    inputManager.addMapping("Start",  new KeyTrigger(KeyInput.KEY_B));
    inputManager.addListener(actionListener, new String[]{"Start"});

	/**********Move******/

    inputManager.addMapping("Forward",  new KeyTrigger(KeyInput.KEY_I));
    inputManager.addListener(actionListener, new String[]{"Forward"});

	inputManager.addMapping("Backward",  new KeyTrigger(KeyInput.KEY_K));
    inputManager.addListener(actionListener, new String[]{"Backward"});

    inputManager.addMapping("Left",  new KeyTrigger(KeyInput.KEY_J));
    inputManager.addListener(actionListener, new String[]{"Left"});

    inputManager.addMapping("Right",  new KeyTrigger(KeyInput.KEY_L));
    inputManager.addListener(actionListener, new String[]{"Right"});

	/**********Rotate******/
	//x
	// You can map one or several inputs to one named action
    inputManager.addMapping("Rotate",  new KeyTrigger(KeyInput.KEY_X));

    // Add the names to the action listener.
    inputManager.addListener(actionListener, new String[]{"Rotate"});

}

private ActionListener actionListener = new ActionListener()
{
	public void onAction(String name, boolean isPressed, float tpf)
	{

		/**********Join******/
        if (name.equals("Start"))
        {

			mJoinGame = true;
			if (mJoinGame && !mPlayingGame)
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
        }


		/**********MOVE******/

		if (name.equals("Forward"))
		{
			mGameMonkey.mNetwork.mCommandToServer.mKey |= mKeyUp;
		}

		if (name.equals("Backward"))
		{
			mGameMonkey.mNetwork.mCommandToServer.mKey |= mKeyDown;
		}

		if (name.equals("Left"))
		{
			mGameMonkey.mNetwork.mCommandToServer.mKey |= mKeyLeft;
		}

		if (name.equals("Right"))
		{
			mGameMonkey.mNetwork.mCommandToServer.mKey |= mKeyRight;
		}

		/**********Rotate******/
		if (name.equals("Rotate"))
        {
			mGameMonkey.mShapeVector.get(0).yaw(.10f,true);
			//mGameMonkey.

        }

		mGameMonkey.mNetwork.mCommandToServer.mMilliseconds = (int) (mGameMonkey.mFrameTime * 1000);

    }
};

//graphics

//Ogre::SceneManager* getSceneManager      () { return mSceneMgr; }

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
	/*
	mGameOgre->mNetwork->mCommandToServer->mKey = 0;

	if (mKeyboard->isKeyDown(OIS::KC_I)) // Forward
    {
		mGameOgre->mNetwork->mCommandToServer->mKey |= mKeyUp;
    }

    if (mKeyboard->isKeyDown(OIS::KC_K)) // Backward
    {
		mGameOgre->mNetwork->mCommandToServer->mKey |= mKeyDown;
    }

	if (mKeyboard->isKeyDown(OIS::KC_J)) // Left - yaw or strafe
    {
		mGameOgre->mNetwork->mCommandToServer->mKey |= mKeyLeft;
    }

    if (mKeyboard->isKeyDown(OIS::KC_L)) // Right - yaw or strafe
    {
		mGameOgre->mNetwork->mCommandToServer->mKey |= mKeyRight;
    }

	mGameOgre->mNetwork->mCommandToServer->mMilliseconds = (int) (mGameOgre->mFrameTime * 1000);
	*/
}




}

