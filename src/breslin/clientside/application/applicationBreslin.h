#ifndef APPLICATIONBRESLIN_H
#define APPLICATIONBRESLIN_H

/***************************************
*   		INCLUDES
***************************************/

//parents
#include "BaseApplication.h"

/***************************************
*   		FORWARD DECLARATIONS
***************************************/
class Game;
class Network;
class StateMachine;
class State;

class ApplicationBreslin : public BaseApplication
{
public:
	
	ApplicationBreslin(const char* serverIP, int serverPort);
	~ApplicationBreslin();

/***************************************
*   		MEMBER VARIABLES
***************************************/

public:

//state machine
StateMachine* mStateMachine;

State* mApplicationGlobal;
State* mApplicationInitialize;
State* mApplicationMain;
State* mApplicationPlay;

//constants
static const char mMessageServerExit = 3;
static const char mMessageConnect     = -101;
static const char mAddSchool          = -109;
static const char mMessageLogin       = -110;
static const char mMessageJoinGame    = -107;
static const char mMessageDisconnect  = -102;

//Network
Network*     mNetwork;

//game
Game* mGame;

//state transition variables
bool mSetup;
bool mPlayingGame;
bool mFake;
bool mConnectSent;

//gui
OgreBites::SelectMenu* mSelectMenuSchool;
OgreBites::Button* mButtonHit;

OgreBites::Label* mLabelUsername;
OgreBites::Label* mLabelPassword;

OgreBites::Button* mButtonLogin;
OgreBites::Button* mButtonJoinGame;
OgreBites::Button* mButtonExit;

private:

//time
float mRenderTime;

/***************************************
*			          METHODS
***************************************/

public:

//process update
void processUpdate();

//time
float getRenderTime();

//scene
Ogre::SceneManager* getSceneManager      () { return mSceneMgr; }

//gui
void createMainScreen();
void showMainScreen();
void hideMainScreen();

//input
OIS::Keyboard* getKeyboard() { return mKeyboard; }

/********* NETWORK *******/
void checkForByteBuffer();

//connect
void sendConnect   ();

//join game
void sendJoinGame();

//login 
void sendLogin();

//shutdown
void shutdown();

//graphics
bool runGraphics();

//camera
Ogre::Camera* getCamera() { return mCamera; }

private:
void createScene          ();

//rendering
virtual bool frameRenderingQueued (const Ogre::FrameEvent& evt);

//input
void buttonHit             (OgreBites::Button *button);
bool mouseMoved            ( const OIS::MouseEvent &arg );
bool keyPressed( const OIS::KeyEvent &arg );

};

#endif
