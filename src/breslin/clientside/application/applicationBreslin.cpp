//header
#include "applicationBreslin.h"

//log
#include "../tdreamsock/dreamSockLog.h"

//shape
#include "../shape/shape.h"

//math
#include "../../math/vector3D.h"

//byteBuffer
#include "../bytebuffer/byteBuffer.h"

//network
#include "../network/network.h"

//command
#include "../command/command.h"

//game
#include "../game/gameTag.h"

//state machine
#include "../../statemachine/stateMachine.h"
#include "states/applicationGlobal.h"
#include "states/applicationMain.h"
#include "states/applicationInitialize.h"
#include "states/applicationPlay.h"


/***************************************
*	CONSTRUCTORS		          
***************************************/
ApplicationBreslin::ApplicationBreslin(const char* serverIP, int serverPort)
{
	StartLog();

	//network
	mNetwork = new Network(this,serverIP,serverPort);

	//initilize
	mSetup = false;
	mPlayingGame = false;
	mFake = true;
	mConnectSent = false;
	mButtonHit = NULL;

	//time
	mRenderTime = 0.0f;

	//game
	mGame = NULL;

	//state machine (Menus)
	mStateMachine = new StateMachine();

	mApplicationGlobal = new ApplicationGlobal(this);
	mApplicationInitialize = new ApplicationInitialize(this);
	mApplicationMain   = new ApplicationMain  (this);
	mApplicationPlay   = new ApplicationPlay(this);

	mStateMachine->setGlobalState (mApplicationGlobal);
	mStateMachine->changeState(mApplicationInitialize);
        mStateMachine->setPreviousState(mApplicationInitialize);
}

ApplicationBreslin::~ApplicationBreslin()
{
	mNetwork->close();
	delete mNetwork;
	
	delete mStateMachine;
	delete mApplicationInitialize;
	delete mApplicationMain;
	delete mApplicationPlay;	
	
	delete mGame;
}

/*********************************
			update
**********************************/
void ApplicationBreslin::processUpdate()
{
	mStateMachine->update();

	if (mFake == true)
	{
		//mGame = new Game(this);

		hideMainScreen();

       		mStateMachine->changeState(mApplicationPlay);

		//sneak an update in
		mStateMachine->update();

		//fake esc from game
  		mPlayingGame = false;
                mStateMachine->changeState(mApplicationMain);
		
		mFake = false;
	}
	
	//did you sendConnect if not do so
	if (!mConnectSent)
	{
		mConnectSent = true; 
		sendConnect();
	}

}

/*********************************
	ADMIN
**********************************/

void ApplicationBreslin::shutdown()
{
	ByteBuffer* byteBuffer = new ByteBuffer();
	byteBuffer->WriteByte(mMessageDisconnect);
	mNetwork->send(byteBuffer);
	mNetwork->reset();
}


/*********************************
		NETWORK
**********************************/

void ApplicationBreslin::sendConnect()
{
	ByteBuffer* byteBuffer = new ByteBuffer();
	byteBuffer->WriteByte(mMessageConnect);
	mNetwork->send(byteBuffer);
}

void ApplicationBreslin::sendJoinGame()
{
	ByteBuffer* byteBuffer = new ByteBuffer();
	byteBuffer->WriteByte(mMessageJoinGame);
	mNetwork->send(byteBuffer);
}

void ApplicationBreslin::checkForByteBuffer()
{
        int type = 0;

        ByteBuffer* byteBuffer = new ByteBuffer();

        while(mNetwork->checkForByteBuffer(byteBuffer))
        {
                byteBuffer->BeginReading();

                type = byteBuffer->ReadByte();

                
		switch(type)
                {
                	case mAddSchool:
                              	LogString("adding school!!!!!!!!!FFFFFF");
				int length = byteBuffer->ReadByte();
				LogString("length of school:%d",length);
				
				for (int i = 0; i < length; i++)
				{
					int b =  byteBuffer->ReadByte(); 
				
					char c = b;
	
					LogString("char:%c",c);	

				}			

				break;
		}


		//pass on to game if there is one....
		if (mGame)
		{
			mGame->checkByteBuffer(byteBuffer);
		}
        }
}


/*********************************

*		TIME
***********************************/
float ApplicationBreslin::getRenderTime()
{
	return mRenderTime;
}


/*********************************
		GRAPHICS
**********************************/
void ApplicationBreslin::createScene()
{
/*
        mSceneMgr->setAmbientLight(Ogre::ColourValue(0.75, 0.75, 0.75));

        Ogre::Light* pointLight = mSceneMgr->createLight("pointLight");
        pointLight->setType(Ogre::Light::LT_POINT);
	pointLight->setPosition(Ogre::Vector3(250, 150, 250));
	pointLight->setDiffuseColour(Ogre::ColourValue::White);
	pointLight->setSpecularColour(Ogre::ColourValue::White);

// create a floor mesh resource
	
        MeshManager::getSingleton().createPlane("floor", ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
	       Plane(Vector3::UNIT_Y, -10), 100, 100, 10, 10, true, 1, 10, 10, Vector3::UNIT_Z);

                // create a floor entity, give it a material, and place it at the origin
        Entity* floor = mSceneMgr->createEntity("Floor", "floor");
        floor->setMaterialName("Examples/Rockwall");
        floor->setCastShadows(false);
        mSceneMgr->getRootSceneNode()->attachObject(floor);
*/
}



bool ApplicationBreslin::runGraphics()
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

bool ApplicationBreslin::frameRenderingQueued(const Ogre::FrameEvent& evt)
{
	mRenderTime = evt.timeSinceLastFrame;

	bool ret = BaseApplication::frameRenderingQueued(evt);
	
	return ret;
}

/*********************************
		GUI
**********************************/

void ApplicationBreslin::createMainScreen()
{
	LogString("create buttons");
	mButtonJoinGame = mTrayMgr->createButton(OgreBites::TL_CENTER, "mButtonJoinGame", "Join Game");
	mButtonExit     = mTrayMgr->createButton(OgreBites::TL_CENTER, "mButtonExit", "Exit Application");
}

void ApplicationBreslin::showMainScreen()
{

	mTrayMgr->moveWidgetToTray(mButtonJoinGame,OgreBites::TL_CENTER);
	mTrayMgr->moveWidgetToTray(mButtonExit,OgreBites::TL_CENTER);
	
	mButtonJoinGame->show();
	mButtonExit->show();
	
	mTrayMgr->showCursor();
}

void ApplicationBreslin::hideMainScreen()
{
	mButtonJoinGame->hide();
	mButtonExit->hide();
}



void ApplicationBreslin::buttonHit(OgreBites::Button *button)
{
	mButtonHit = button;
}

bool ApplicationBreslin::mouseMoved( const OIS::MouseEvent &arg )
{
	if (mTrayMgr->injectMouseMove(arg))
	{
		return true;
	}
	if (mPlayingGame)
	{
		mCameraMan->injectMouseMove(arg);
	}
    return true;
}

