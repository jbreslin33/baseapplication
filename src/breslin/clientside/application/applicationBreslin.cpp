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
#include "states/applicationLogin.h"
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

	//time
	mRenderTime = 0.0f;

	//game
	mGame = NULL;

	//state machine (Menus)
	mStateMachine = new StateMachine();

	mApplicationGlobal     = new ApplicationGlobal    (this);
	mApplicationInitialize = new ApplicationInitialize(this);
	mApplicationMain       = new ApplicationMain      (this);
	mApplicationPlay       = new ApplicationPlay      (this);
	mApplicationLogin      = new ApplicationLogin     (this);

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
	delete mApplicationLogin;
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
		//after first update let's fake going to game with no sendCnnect...
		mButtonHit = NULL;
        	//	sendConnect();
       		mGame = new Game(this);

		hideLoginScreen();

       		mStateMachine->changeState(mApplicationPlay);

		//sneak an update in
		mStateMachine->update();

		//fake esc from game
  		mPlayingGame = false;
                mStateMachine->changeState(mApplicationLogin);
		
		mFake = false;
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
/*
	ByteBuffer* byteBuffer = new ByteBuffer();
	byteBuffer->WriteByte(mMessageConnect);
	mNetwork->send(byteBuffer);
*/
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
        LogString("create Login buttons");
        mLabelUsername = mTrayMgr->createLabel(OgreBites::TL_CENTER, "mLabelUsername", "Username:");

        mButtonLogin     = mTrayMgr->createButton(OgreBites::TL_CENTER, "mButtonLogin", "Login");
        mButtonSignup    = mTrayMgr->createButton(OgreBites::TL_CENTER, "mButtonSignup", "Signup");
        mButtonPractice  = mTrayMgr->createButton(OgreBites::TL_CENTER, "mButtonPractice", "Practice");
        mButtonExit      = mTrayMgr->createButton(OgreBites::TL_CENTER, "mButtonExit", "Exit Application");
}

void ApplicationBreslin::showLoginScreen()
{

        mTrayMgr->moveWidgetToTray(mLabelUsername,OgreBites::TL_CENTER);
        mTrayMgr->moveWidgetToTray(mButtonLogin,OgreBites::TL_CENTER);
        mTrayMgr->moveWidgetToTray(mButtonSignup,OgreBites::TL_CENTER);
        mTrayMgr->moveWidgetToTray(mButtonPractice,OgreBites::TL_CENTER);
        mTrayMgr->moveWidgetToTray(mButtonExit,OgreBites::TL_CENTER);

        mLabelUsername->show();
        mButtonLogin->show();
        mButtonSignup->show();
        mButtonPractice->show();
        mButtonExit->show();

        mTrayMgr->showCursor();
}

void ApplicationBreslin::hideLoginScreen()
{
        mLabelUsername->hide();
        mButtonLogin->hide();
        mButtonSignup->hide();
        mButtonPractice->hide();
        mButtonExit->hide();
}

//MAIN
void ApplicationBreslin::createMainScreen()
{
	LogString("create Main buttons");
	mButtonGame = mTrayMgr->createButton(OgreBites::TL_CENTER, "mButtonGame", "Join Game");
	mButtonTag = mTrayMgr->createButton(OgreBites::TL_CENTER, "mButtonTag", "Join Tag");
	mButtonTagAll = mTrayMgr->createButton(OgreBites::TL_CENTER, "mButtonTagAll", "Join TagAll");
	mButtonExit = mTrayMgr->createButton(OgreBites::TL_CENTER, "mButtonExit", "Exit Application");
}

void ApplicationBreslin::showMainScreen()
{

	mTrayMgr->moveWidgetToTray(mButtonGame,OgreBites::TL_CENTER);
	mTrayMgr->moveWidgetToTray(mButtonTag,OgreBites::TL_CENTER);
	mTrayMgr->moveWidgetToTray(mButtonTagAll,OgreBites::TL_CENTER);
	mTrayMgr->moveWidgetToTray(mButtonExit,OgreBites::TL_CENTER);
	
	mButtonGame->show();
	mButtonTag->show();	
	mButtonTagAll->show();	
	mButtonExit->show();
	
	mTrayMgr->showCursor();
}

void ApplicationBreslin::hideMainScreen()
{
	mButtonGame->hide();
	mButtonTag->hide();	
	mButtonTagAll->hide();	
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

