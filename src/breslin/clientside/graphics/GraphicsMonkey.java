package breslin.clientside.graphics;

/***************************************
*   		INCLUDES
***************************************/
//standard library

//parent
import com.jme3.app.SimpleApplication;

//game
import breslin.clientside.game.GameMonkey;

//input
import com.jme3.input.KeyInput;
import com.jme3.input.controls.ActionListener;
import com.jme3.input.controls.KeyTrigger;


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
	// You can map one or several inputs to one named action
    inputManager.addMapping("Start",  new KeyTrigger(KeyInput.KEY_B));

    // Add the names to the action listener.
    inputManager.addListener(actionListener, new String[]{"Start"});

}

private ActionListener actionListener = new ActionListener()
{
	public void onAction(String name, boolean isPressed, float tpf)
	{
        if (name.equals("Start"))
        {

			mJoinGame = true;
			if (mJoinGame && !mPlayingGame)
			{
				System.out.println("send Connect.....");
				mGameMonkey.mNetwork.sendConnect();
				mPlayingGame = true;
			}
        }
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

