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
#include "../game/game.h"

//state machine
#include "../../statemachine/stateMachine.h"
#include "states/applicationGlobal.h"
#include "states/applicationLogin.h"
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
	//state transition variables
	mSetup = false;
	mConnected = false;
	mPlayingGame = false;
	mFake = true;
	mConnectSent = false;
	mButtonHit = NULL;
	mLoggedIn = false;
        mLeaveGame = false;
        mSentLeaveGame = false;

	//time
	mRenderTime = 0.0f;

	//game
	mGame = NULL;

	mStateMachine = new StateMachine();
}


ApplicationBreslin::~ApplicationBreslin()
{
	mNetwork->close();
	delete mNetwork;
	
	delete mStateMachine;
	delete mApplicationInitialize;
	delete mApplicationLogin;
	delete mApplicationMain;
	delete mApplicationPlay;	
	
	delete mGame;
}

/*********************************
			states	
**********************************/
void ApplicationBreslin::createStates()
{
	LogString("ApplicationBreslin::createStates");
	mApplicationGlobal     = new ApplicationGlobal(this);
	mApplicationInitialize = new ApplicationInitialize(this);
	mApplicationLogin      = new ApplicationLogin  (this);
	mApplicationMain       = new ApplicationMain  (this);
	mApplicationPlay       = new ApplicationPlay(this);

}

void ApplicationBreslin::setStates()
{
	LogString("ApplicationBreslin::setStates");
	mStateMachine->setGlobalState (mApplicationGlobal);
	mStateMachine->changeState(mApplicationInitialize);
        mStateMachine->setPreviousState(mApplicationInitialize);
}

/*********************************
			update
**********************************/
void ApplicationBreslin::processUpdate()
{
	mStateMachine->update();

	if (mFake == true)
	{
		createLoginScreen();
		hideLoginScreen();
 		
		mGame = new Game(this);
		mGame->createStates();
		mGame->setStates();
       		mStateMachine->changeState(mApplicationPlay);

		//sneak an update in
		mStateMachine->update();

		//fake esc from game
  		mPlayingGame = false;
                mStateMachine->changeState(mApplicationLogin);
		
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

void ApplicationBreslin::sendLogin()
{
	ByteBuffer* byteBuffer = new ByteBuffer();
	byteBuffer->WriteByte(mMessageLogin);

	//get length of username
	int sizeOfUsername = mStringUsername.size();

	//write length of username
	byteBuffer->WriteByte(sizeOfUsername);

	//get length of password
	int sizeOfPassword = mStringPassword.size();
	
	//write length of password 
	byteBuffer->WriteByte(sizeOfPassword);
	
	//loop thru username string
	for (int i = 0; i < sizeOfUsername; i++)
	{
		//write individual char of mStringUsername
		byteBuffer->WriteByte(mStringUsername.at(i));	
	}

	//loop thru password  string
	for (int i = 0; i < sizeOfPassword; i++)
	{
		//write individual char of mStringPassword
		byteBuffer->WriteByte(mStringPassword.at(i));	
	}

	//send it off to server
	mNetwork->send(byteBuffer);
}

void ApplicationBreslin::sendLogout()
{
	ByteBuffer* byteBuffer = new ByteBuffer();
	byteBuffer->WriteByte(mMessageLogout);
	
	//send it off to server
	mNetwork->send(byteBuffer);
}

void ApplicationBreslin::sendJoinGame(int gameID)
{
	ByteBuffer* byteBuffer = new ByteBuffer();
	byteBuffer->WriteByte(mMessageJoinGame);
	byteBuffer->WriteByte(gameID);
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

		if (type == mMessageConnected)
		{
			LogString("mConnected = true");
			mConnected = true;
		}

		if (type == mMessageAddSchool)
		{
			LogString("adding school..");
			std::string school;
			int length = byteBuffer->ReadByte();
			for (int i = 0; i < length; i++)
			{
				char c =  byteBuffer->ReadByte(); 
                                school.append(1,c);
			}			
			mSelectMenuSchool->addItem(school);
		}

		if (type == mMessageLoggedIn)
		{
			LogString("LoggedIn");
			mLoggedIn = true;
		}

		if (type == mMessageLoggedOut)
		{
			LogString("LoggedOut");
			mLoggedIn = false;
		}

		if (type == mMessageLeaveGame)
		{
			mLeaveGame = true;
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

//LOGIN
void ApplicationBreslin::createLoginScreen()
{
	LogString("createLoginScreen what");
	if (!mSelectMenuSchool)
	{
        	mSelectMenuSchool = mTrayMgr->createThickSelectMenu(OgreBites::TL_CENTER, "mSelectMenuSchool", "Select School", 120, 10);
	}
	
	if (!mLabelUsername)
	{
        	mLabelUsername  = mTrayMgr->createLabel(OgreBites::TL_CENTER, "mLabelUsername", "Username:");
	}

	if (!mLabelPassword)
	{
        	mLabelPassword  = mTrayMgr->createLabel(OgreBites::TL_CENTER, "mLabelPassword", "Password:");
	}

	if (!mButtonLogin)
	{
        	mButtonLogin    = mTrayMgr->createButton(OgreBites::TL_CENTER, "mButtonLogin", "Login");
	}
		
	if (!mButtonExit)
	{
        	mButtonExit     = mTrayMgr->createButton(OgreBites::TL_CENTER, "mButtonExit", "Exit Application");
	}
}

void ApplicationBreslin::showLoginScreen()
{
	LogString("showLoginScreen");
        mTrayMgr->moveWidgetToTray(mSelectMenuSchool,OgreBites::TL_CENTER);
        mTrayMgr->moveWidgetToTray(mLabelUsername,OgreBites::TL_CENTER);
        mTrayMgr->moveWidgetToTray(mLabelPassword,OgreBites::TL_CENTER);
        mTrayMgr->moveWidgetToTray(mButtonLogin,OgreBites::TL_CENTER);
        mTrayMgr->moveWidgetToTray(mButtonExit,OgreBites::TL_CENTER);

        mSelectMenuSchool->show();
        mLabelUsername->show();
        mLabelPassword->show();
        mButtonLogin->show();
        mButtonExit->show();

        mTrayMgr->showCursor();

        //set intial focus on username
        mLabelFocus = mLabelUsername;
}

void ApplicationBreslin::hideLoginScreen()
{
	LogString("hideLoginScreen");
        mSelectMenuSchool->hide();
        mLabelUsername->hide();
        mLabelPassword->hide();
        mButtonLogin->hide();
        mButtonExit->hide();

        mTrayMgr->removeWidgetFromTray(mSelectMenuSchool);
        mTrayMgr->removeWidgetFromTray(mLabelUsername);
        mTrayMgr->removeWidgetFromTray(mLabelPassword);
        mTrayMgr->removeWidgetFromTray(mButtonLogin);
        mTrayMgr->removeWidgetFromTray(mButtonExit);
}


//MAIN
void ApplicationBreslin::createMainScreen()
{
	LogString("createMainScreen");
	if (!mButtonJoinGameA)
	{
		mButtonJoinGameA = mTrayMgr->createButton(OgreBites::TL_CENTER, "mButtonJoinGameA", "Join Game A");
	}

	if (!mButtonLogout)
	{
        	mButtonLogout    = mTrayMgr->createButton(OgreBites::TL_CENTER, "mButtonLogout", "Logout");
	}

	if (!mButtonExit)
	{
		mButtonExit     = mTrayMgr->createButton(OgreBites::TL_CENTER, "mButtonExit", "Exit Application");
	}
}

void ApplicationBreslin::showMainScreen()
{
	LogString("showMainScreen");
	mTrayMgr->moveWidgetToTray(mButtonJoinGameA,OgreBites::TL_CENTER);
	mTrayMgr->moveWidgetToTray(mButtonLogout,OgreBites::TL_CENTER);
	mTrayMgr->moveWidgetToTray(mButtonExit,OgreBites::TL_CENTER);
	
	mButtonJoinGameA->show();
	mButtonLogout->show();
	mButtonExit->show();
	
	mTrayMgr->showCursor();

	//set intial focus on username
	mLabelFocus = mLabelUsername;

}

void ApplicationBreslin::hideMainScreen()
{
	LogString("hideMainScreen");
	mButtonJoinGameA->hide();
	mButtonLogout->hide();
	mButtonExit->hide();

	mTrayMgr->removeWidgetFromTray(mButtonJoinGameA);
	mTrayMgr->removeWidgetFromTray(mButtonLogout);
	mTrayMgr->removeWidgetFromTray(mButtonExit);
}

//battle
void  ApplicationBreslin::createBattleScreen()
{
        LogString("ApplicationBreslin::createBattleScreen");
	if (!mLabelQuestion)
	{
                LogString("ApplicationBreslin::createBattleScreen 0");

                mLabelQuestion  = mTrayMgr->createLabel(OgreBites::TL_CENTER, "mLabelQuestion", "Question:");

	}
        if (!mLabelQuestion)
        {
                LogString("ApplicationBreslin::createBattleScreen 0");
                mLabelQuestion  = mTrayMgr->createLabel(OgreBites::TL_CENTER, "mLabelQuestion", "Question:");
        }
        if (!mLabelAnswer)
        {
                mLabelAnswer  = mTrayMgr->createLabel(OgreBites::TL_CENTER, "mLabelAnswer", "Answer:");
        }
}

void  ApplicationBreslin::showBattleScreen()
{
/*
        mTrayMgr->moveWidgetToTray(mLabelQuestion,OgreBites::TL_CENTER);
        mTrayMgr->moveWidgetToTray(mLabelAnswer,OgreBites::TL_CENTER);

        mLabelQuestion->show();
        mLabelAnswer->show();

        mTrayMgr->showCursor();

        mLabelFocus = mLabelAnswer;
*/
}

void  ApplicationBreslin::hideBattleScreen()
{
        mLabelQuestion->hide();
        mLabelAnswer->hide();

        mTrayMgr->removeWidgetFromTray(mLabelQuestion);
        mTrayMgr->removeWidgetFromTray(mLabelAnswer);
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

bool ApplicationBreslin::keyPressed( const OIS::KeyEvent &arg )
{
	if (mStateMachine->getCurrentState() == mApplicationLogin)
	{

		if (mLabelFocus == mLabelUsername)
		{
			int numeric = arg.text;
			char ascii = (char)numeric;	

			if (numeric == 8) //backspace
			{
				int size = mStringUsername.size();
				if (size > 0)
				{
					mStringUsername.resize(size - 1);
				}
				mLabelUsername->setCaption(mStringUsername);
			}

			if (numeric == 9) //tab
			{
				mLabelFocus = mLabelPassword;
			}
			
			if (numeric > 47 && numeric < 123) //letters and valid symbols for username and password
			{
				mStringUsername.append(1,ascii);
				mLabelUsername->setCaption(mStringUsername);
			}
		}

		if (mLabelFocus == mLabelPassword)
		{
 			int numeric = arg.text;
                	char ascii = (char)numeric;

                	if (numeric == 8) //backspace
                	{
                        	int size = mStringPassword.size();
				if (size > 0)
				{
                        		mStringPassword.resize(size - 1);
				}
                        	mLabelPassword->setCaption(mStringPassword);
                	}

                	if (numeric == 9) //tab
                	{
                        	//mLabelFocus = mButtonLogin;
                	}

                	if (numeric > 47 && numeric < 123) //letters and valid symbols for username and password
                	{
                        	mStringPassword.append(1,ascii);
                        	mLabelPassword->setCaption(mStringPassword);
                	}
		}
	}
}

void ApplicationBreslin::labelHit( OgreBites::Label* label )
{
	//set pointer to label that is focused so you can write keypressed to it 
	mLabelFocus = label;
}

