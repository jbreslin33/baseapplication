//header
#include "graphicsOgre.h"

//game
#include "../game/applicationOgre.h"

//network
#include "../network/network.h"

//command
#include "../command/command.h"

//shape
#include "../shape/shapeDynamic.h" //only need this to tes Yaw you can pull it out later.

//Ogre headers
#include "Ogre.h"
using namespace Ogre;

GraphicsOgre::GraphicsOgre(ApplicationOgre* applicationOgre)
{
	//game
	mApplicationOgre = applicationOgre;

	//time
	mRenderTime = 0;

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
		initializeGui();
		return false;
	}
	else
	{
		initializeGui();
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
			mApplicationOgre->mNetwork->sendConnect();
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

void GraphicsOgre::processInput()
{
	mApplicationOgre->mNetwork->mCommandToServer->mKey = 0;
    
	if (mKeyboard->isKeyDown(OIS::KC_I)) // Forward
    {
		mApplicationOgre->mNetwork->mCommandToServer->mKey |= mKeyUp;
    }

    if (mKeyboard->isKeyDown(OIS::KC_K)) // Backward
    {
		mApplicationOgre->mNetwork->mCommandToServer->mKey |= mKeyDown;
    }

	if (mKeyboard->isKeyDown(OIS::KC_J)) // Left
    {
		mApplicationOgre->mNetwork->mCommandToServer->mKey |= mKeyLeft;
    }

    if (mKeyboard->isKeyDown(OIS::KC_L)) // Right
    {
		mApplicationOgre->mNetwork->mCommandToServer->mKey |= mKeyRight;
    }
    
	if (mKeyboard->isKeyDown(OIS::KC_Z)) // Rotate -Yaw(counter-clockwise)
    {
		mApplicationOgre->mNetwork->mCommandToServer->mKey |= mKeyCounterClockwise;
    }

    if (mKeyboard->isKeyDown(OIS::KC_X)) // Right + Yaw(clockwise)
    {
		mApplicationOgre->mNetwork->mCommandToServer->mKey |= mKeyClockwise;
    }


	mApplicationOgre->mNetwork->mCommandToServer->mMilliseconds = (int) (mApplicationOgre->mFrameTime * 1000);
}


