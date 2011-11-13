//header
#include "applicationOgre.h"

//standard library
#include <string>

//log
#include "../tdreamsock/dreamSockLog.h"

//network
#include "../network/network.h"

//game
#include "gameOgre.h"

//shape
#include "../shape/shapeOgre.h"

//ability
#include "../ability/rotation/abilityRotation.h"
#include "../ability/move/abilityMove.h"


/*********************************
*		CONSTRUCTORS
**********************************/
ApplicationOgre::ApplicationOgre(const char* serverIP, int serverPort) : Application(serverIP, serverPort) 

{
	mGame = new GameOgre(this,serverIP,serverPort);
}

ApplicationOgre::~ApplicationOgre()
{
}

/*********************************
*		TIME
***********************************/
float ApplicationOgre::getRenderTime()
{
	//LogString("r:%f",mGraphicsOgre->mRenderTime);
	return mRenderTime;
}


/*********************************
		GRAPHICS
**********************************/
void ApplicationOgre::createScene(void)
{
    mSceneMgr->setAmbientLight(Ogre::ColourValue(0.75, 0.75, 0.75));

    Ogre::Light* pointLight = mSceneMgr->createLight("pointLight");
    pointLight->setType(Ogre::Light::LT_POINT);
    pointLight->setPosition(Ogre::Vector3(250, 150, 250));
    pointLight->setDiffuseColour(Ogre::ColourValue::White);
    pointLight->setSpecularColour(Ogre::ColourValue::White);
}

bool ApplicationOgre::frameRenderingQueued(const Ogre::FrameEvent& evt)
{
	mRenderTime = evt.timeSinceLastFrame;

    bool ret = BaseApplication::frameRenderingQueued(evt);
	
	return ret;
}

bool ApplicationOgre::runGraphics()
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
void ApplicationOgre::initializeGui()
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

void ApplicationOgre::loadJoinScreen()
{
	unloadOtherScreens();
	mJoinButton = mTrayMgr->createButton(OgreBites::TL_CENTER, "mJoinButton", "Join Game");
	mTrayMgr->moveWidgetToTray(mJoinButton,OgreBites::TL_CENTER);
	mTrayMgr->showCursor();
}

void ApplicationOgre::hideGui()
{
	hideJoinScreen();
	mTrayMgr->hideCursor();
}

void ApplicationOgre::hideJoinScreen()
{
	mTrayMgr->removeWidgetFromTray(mJoinButton);
    mJoinButton->hide();
}

void ApplicationOgre::unloadOtherScreens()
{
}

/***************************************
*			INPUT
******************************************/

void ApplicationOgre::buttonHit(OgreBites::Button *button)
{
	if (button == mJoinButton)
	{
		mJoinGame = true;
		if (mJoinGame && !mPlayingGame)
		{
			mNetwork->sendConnect();
			//LogString("sent connect to server");
			mPlayingGame = true;
		}

		hideGui();
	}
}

bool ApplicationOgre::mouseMoved( const OIS::MouseEvent &arg )
{
    if (mTrayMgr->injectMouseMove(arg)) return true;
	if (mPlayingGame)
	{
		mCameraMan->injectMouseMove(arg);
	}
    return true;
}

void ApplicationOgre::processInput()
{
	mNetwork->mCommandToServer->mKey = 0;
    
	if (mKeyboard->isKeyDown(OIS::KC_I)) // Forward
    {
		mNetwork->mCommandToServer->mKey |= mKeyUp;
    }

    if (mKeyboard->isKeyDown(OIS::KC_K)) // Backward
    {
		mNetwork->mCommandToServer->mKey |= mKeyDown;
    }

	if (mKeyboard->isKeyDown(OIS::KC_J)) // Left
    {
		mNetwork->mCommandToServer->mKey |= mKeyLeft;
    }

    if (mKeyboard->isKeyDown(OIS::KC_L)) // Right
    {
		mNetwork->mCommandToServer->mKey |= mKeyRight;
    }
    
	if (mKeyboard->isKeyDown(OIS::KC_Z)) // Rotate -Yaw(counter-clockwise)
    {
		mNetwork->mCommandToServer->mKey |= mKeyCounterClockwise;
    }

    if (mKeyboard->isKeyDown(OIS::KC_X)) // Right + Yaw(clockwise)
    {
		mNetwork->mCommandToServer->mKey |= mKeyClockwise;
    }


	mNetwork->mCommandToServer->mMilliseconds = (int) (mFrameTime * 1000);
}


