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
import com.jme3.input.controls.AnalogListener;
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
	System.out.println("initialize keys with initKeys");
    initKeys(); // load my custom keybinding
}

//input
private void initKeys()
{
	// You can map one or several inputs to one named action
    inputManager.addMapping("Start",  new KeyTrigger(KeyInput.KEY_B));

    // Add the names to the action listener.
    inputManager.addListener(analogListener, new String[]{"Start"});

}

private AnalogListener analogListener = new AnalogListener()
{
	public void onAnalog(String name, float value, float tpf)
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
boolean                runGraphics          ()
{
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

}
}

