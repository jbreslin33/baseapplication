package breslin.clientside.graphics;

/***************************************
*   		INCLUDES
***************************************/
//standard library

//parent
import com.jme3.app.SimpleApplication;

//game
import breslin.clientside.game.GameMonkey;

/***************************************
*   		FORWARD DECLARATIONS
***************************************/

public class GraphicsMonkey extends SimpleApplication
{

public GraphicsMonkey(GameMonkey gameMonkey)
{

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
//bool mouseMoved            ( const OIS::MouseEvent &arg );
void processInput()
{

}
}

