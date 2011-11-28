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


/***************************************
*	CONSTRUCTORS		          
***************************************/
ApplicationBreslin::ApplicationBreslin(const char* serverIP, int serverPort)
{
	StartLog();

	//network
	mNetwork = new Network(this,serverIP,serverPort);

	//time
	mFrameTime = 0.0f;
	mRenderTime = 0.0f;
	mRunNetworkTime = 0.0f;

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

	//game
	mGame = new Game(this);

	//input
	mKeyCurrent = 0;
	mKeyLast = 0;
	mMillisecondsCurrent = 0;
	mMillisecondsLast = 0;

	//sequence
	mOutgoingSequence		= 1;
}

ApplicationBreslin::~ApplicationBreslin()
{
	mNetwork->close();
	delete mNetwork;
}

/*********************************
	LOOP
**********************************/
void ApplicationBreslin::run()
{
	while(true)
    	{
		//input
		processInput();
		
		//network
		runNetwork(getRenderTime() * 1000.0f);
		
		//game
		mGame->run();

		//graphics
		if (!runGraphics())
		{
			break;
		}
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
void ApplicationBreslin::runNetwork(float msec)
{
	mRunNetworkTime += msec;

	readPackets();
	
	// Framerate is too high
	if(mRunNetworkTime > (1000 / 60))
	{
		sendCommand();
		mFrameTime = mRunNetworkTime / 1000.0f;
		mRunNetworkTime = 0.0f;
	}
}

void ApplicationBreslin::readPackets()
{
	int type = 0;

	ByteBuffer* byteBuffer = new ByteBuffer();

	while(mNetwork->checkForByteBuffer(byteBuffer))
	{
		byteBuffer->BeginReading();

		type = byteBuffer->ReadByte();

		switch(type)
		{
			case mMessageConnect:
			break;

			case mMessageAddShape:
				if (mGame)
				{
					mGame->addShape(true,byteBuffer);
				}
			break;

			case mMessageRemoveShape:
				if (mGame)
				{
					mGame->removeShape(byteBuffer);
				}
			break;

			case mMessageFrame:
				readServerTick(byteBuffer);
			break;

			case mMessageServerExit:
				shutdown();
			break;
		}
	}
}

void ApplicationBreslin::sendCommand()
{
	//create byteBuffer
	ByteBuffer* byteBuffer = new ByteBuffer();

	//WRITE: type
	byteBuffer->WriteByte(mMessageFrame);					
	
	//WRITE: sequence
	byteBuffer->WriteShort(mOutgoingSequence);
	
	mOutgoingSequence++; //increase for next time...

	// Build delta-compressed move command
	int flags = 0;

	// Check what needs to be updated
	if(mKeyLast != mKeyCurrent)
	{
		flags |= mCommandKey;
	}

	if(mMillisecondsLast != mMillisecondsCurrent)
	{
		flags |= mCommandMilliseconds;
	}
	
	// Add to the message
	byteBuffer->WriteByte(flags);

	if(flags & mCommandKey)
	{
		//WRITE: key
		byteBuffer->WriteByte(mKeyCurrent);
	}

	if(flags & mCommandMilliseconds)
	{
		//WRITE: milliseconds
		byteBuffer->WriteByte(mMillisecondsCurrent);
	}
	
	//set 'last' commands for diff
	mKeyLast = mKeyCurrent;
	mMillisecondsLast = mMillisecondsCurrent;

	// Send the packet
	mNetwork->send(byteBuffer);
}

void ApplicationBreslin::sendConnect()
{
	ByteBuffer* byteBuffer = new ByteBuffer();
	byteBuffer->WriteByte(mMessageConnect);
	mNetwork->send(byteBuffer);
}


void ApplicationBreslin::readServerTick(ByteBuffer* byteBuffer)
{
	// Skip sequences
	short sequence = byteBuffer->ReadShort();

	while (byteBuffer->getReadCount() <= byteBuffer->GetSize())
	{
		//mDetailsPanel->setParamValue(11, Ogre::StringConverter::toString(byteBuffer->GetSize()));

		int id = byteBuffer->ReadByte();

		Shape* shape = NULL;
		if (mGame)
		{
			shape = mGame->getShape(id);
		}
		else
		{
			LogString("GAME IS NULL");
		}
		if (shape)
		{
			shape->processDeltaByteBuffer(byteBuffer);
		}
		else
		{
			//LogString("INVALID SHAPE ID");
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
        mSceneMgr->setAmbientLight(Ogre::ColourValue(0.75, 0.75, 0.75));

        Ogre::Light* pointLight = mSceneMgr->createLight("pointLight");
        pointLight->setType(Ogre::Light::LT_POINT);
	pointLight->setPosition(Ogre::Vector3(250, 150, 250));
	pointLight->setDiffuseColour(Ogre::ColourValue::White);
	pointLight->setSpecularColour(Ogre::ColourValue::White);
}

bool ApplicationBreslin::runGraphics()
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

bool ApplicationBreslin::frameRenderingQueued(const Ogre::FrameEvent& evt)
{
	mRenderTime = evt.timeSinceLastFrame;

	bool ret = BaseApplication::frameRenderingQueued(evt);
	
	return ret;
}

/*********************************
		GUI
**********************************/
void ApplicationBreslin::initializeGui()
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

void ApplicationBreslin::loadJoinScreen()
{
	mJoinButton = mTrayMgr->createButton(OgreBites::TL_CENTER, "mJoinButton", "Join Game");
	mTrayMgr->moveWidgetToTray(mJoinButton,OgreBites::TL_CENTER);
	mTrayMgr->showCursor();
}

void ApplicationBreslin::hideGui()
{
	hideJoinScreen();
	mTrayMgr->hideCursor();
}

void ApplicationBreslin::hideJoinScreen()
{
	mTrayMgr->removeWidgetFromTray(mJoinButton);
    mJoinButton->hide();
}


/***************************************
*			INPUT
******************************************/


void ApplicationBreslin::processInput()
{
	mKeyCurrent = 0;
    
	if (mKeyboard->isKeyDown(OIS::KC_I)) // Forward
    {
		mKeyCurrent |= mKeyUp;
    }

    if (mKeyboard->isKeyDown(OIS::KC_K)) // Backward
    {
		mKeyCurrent |= mKeyDown;
    }

	if (mKeyboard->isKeyDown(OIS::KC_J)) // Left
    {
		mKeyCurrent |= mKeyLeft;
    }

    if (mKeyboard->isKeyDown(OIS::KC_L)) // Right
    {
		mKeyCurrent |= mKeyRight;
    }
    
	if (mKeyboard->isKeyDown(OIS::KC_Z)) // Rotate -Yaw(counter-clockwise)
    {
		mKeyCurrent |= mKeyCounterClockwise;
    }

    if (mKeyboard->isKeyDown(OIS::KC_X)) // Right + Yaw(clockwise)
    {
		mKeyCurrent |= mKeyClockwise;
    }
	mMillisecondsCurrent = (int) (mFrameTime * 1000);
}

void ApplicationBreslin::buttonHit(OgreBites::Button *button)
{
	//JOIN
	if (button == mJoinButton)
	{
		mJoinGame = true;
		if (mJoinGame && !mPlayingGame)
		{
			sendConnect();
			mPlayingGame = true;
		}
		hideGui();
	}
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

