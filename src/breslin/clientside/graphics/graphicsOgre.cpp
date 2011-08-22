//header
#include "graphicsOgre.h"

//game
#include "../game/gameOgre.h"

//Ogre headers
#include "Ogre.h"
using namespace Ogre;

GraphicsOgre::GraphicsOgre(GameOgre* gameOgre)
{
	//game
	mGameOgre = gameOgre;

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
}

GraphicsOgre::~GraphicsOgre()
{

}


/*********************************
		GRAPHICS
**********************************/
void GraphicsOgre::createScene(void)
{
    mSceneMgr->setAmbientLight(Ogre::ColourValue(0.75, 0.75, 0.75));

    Ogre::Light* pointLight = mSceneMgr->createLight("pointLight");
    pointLight->setType(Ogre::Light::LT_POINT);
    pointLight->setPosition(Ogre::Vector3(250, 150, 250));
    pointLight->setDiffuseColour(Ogre::ColourValue::White);
    pointLight->setSpecularColour(Ogre::ColourValue::White);
}

bool GraphicsOgre::frameRenderingQueued(const Ogre::FrameEvent& evt)
{
	mRenderTime = evt.timeSinceLastFrame;

    bool ret = BaseApplication::frameRenderingQueued(evt);
	
	return ret;
}

bool GraphicsOgre::runGraphics()
{
	//Pump messages in all registered RenderWindow windows
	WindowEventUtilities::messagePump();

	if (!mRoot->renderOneFrame())
	{
		return false;
	}
	else
	{
		return true;
	}
}

/*********************************
		GUI
**********************************/
void GraphicsOgre::initializeGui()
{
	if (mInitializeGui == true)
	{
		return;
	}
	else
	{
		loadJoinScreen();
		mInitializeGui = true;
	}
}

void GraphicsOgre::loadJoinScreen()
{
	unloadOtherScreens();
	mJoinButton = mTrayMgr->createButton(OgreBites::TL_CENTER, "mJoinButton", "Join Game");
	mTrayMgr->moveWidgetToTray(mJoinButton,OgreBites::TL_CENTER);
	mTrayMgr->showCursor();
}

void GraphicsOgre::hideGui()
{
	hideJoinScreen();
	mTrayMgr->hideCursor();
}

void GraphicsOgre::hideJoinScreen()
{
	mTrayMgr->removeWidgetFromTray(mJoinButton);
    mJoinButton->hide();
}

void GraphicsOgre::unloadOtherScreens()
{
}

/***************************************
*			INPUT
******************************************/

void GraphicsOgre::buttonHit(OgreBites::Button *button)
{
	if (button == mJoinButton)
	{
		mJoinGame = true;
		if (mJoinGame && !mPlayingGame)
		{
			mGameOgre->sendConnect("myname");
			//LogString("sent connect to server");
			mPlayingGame = true;
		}

		hideGui();
	}
}

bool GraphicsOgre::mouseMoved( const OIS::MouseEvent &arg )
{
    if (mTrayMgr->injectMouseMove(arg)) return true;
	if (mPlayingGame)
	{
		mCameraMan->injectMouseMove(arg);
	}
    return true;
}

void GraphicsOgre::processUnbufferedInput()
{
	mGameOgre->mCommandToServer->mKey = 0;
    
	if (mKeyboard->isKeyDown(OIS::KC_ESCAPE)) // ESCAPE
    {
		mGameOgre->mNetworkShutdown = true;
    }
	else
	{
		mGameOgre->mNetworkShutdown = false;
	}
    	
	if (mKeyboard->isKeyDown(OIS::KC_I)) // Forward
    {
		mGameOgre->mCommandToServer->mKey |= mKeyUp;
    }

    if (mKeyboard->isKeyDown(OIS::KC_K)) // Backward
    {
		mGameOgre->mCommandToServer->mKey |= mKeyDown;
    }

	if (mKeyboard->isKeyDown(OIS::KC_J)) // Left - yaw or strafe
    {
		mGameOgre->mCommandToServer->mKey |= mKeyLeft;
    }

    if (mKeyboard->isKeyDown(OIS::KC_L)) // Right - yaw or strafe
    {
		mGameOgre->mCommandToServer->mKey |= mKeyRight;
    }

	mGameOgre->mCommandToServer->mMilliseconds = (int) (mGameOgre->mFrameTime * 1000);
}


