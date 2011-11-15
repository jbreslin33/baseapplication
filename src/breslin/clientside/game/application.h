#ifndef APPLICATION_H
#define APPLICATION_H

/***************************************
*   		INCLUDES
***************************************/

//parents
#include "../game/BaseApplication.h"

/***************************************
*   		FORWARD DECLARATIONS
***************************************/
class Game;
class ByteBuffer;
class Shape;
class Time;
class Network;

class Application : public BaseApplication
{
public:
	
	Application(const char* serverIP, int serverPort);
	~Application();

/***************************************
*   		MEMBER VARIABLES
***************************************/

public:

//game
Game* mGame;

//key input
int mKeyCurrent;         
int mKeyLast;

int mMillisecondsCurrent;
int mMillisecondsLast;

//parsers
static const char mCommandMilliseconds = 2;
static const char mMessageFrame = 1;
static const char mCommandKey          = 1;
static const char mMessageConnect     = -101;
static const char mMessageDisconnect  = -102;
static const char mMessageAddShape    = -103;
static const char mMessageRemoveShape = -104;

static const char mMessageNonDeltaFrame = 2;
static const char mMessageServerExit = 3;
static const char mMessageKeepAlive = 12;

//network flags
static const char mCommandOriginX      = 4;
static const char mCommandOriginY      = 8;
static const char mCommandOriginZ      = 16;
static const char mCommandRotationX    = 32;
static const char mCommandRotationZ    = 64;

private:

//sequences and packet loss stats
signed short	mOutgoingSequence;		// OutFgoing packet sequence

//Network
Network*     mNetwork;

//time
float mFrameTime;

//initialize
bool mInitializeGui;
bool mJoinGame;
bool mPlayingGame;

//time
float mRenderTime;

//keys
int mKeyUp;
int mKeyDown;
int mKeyLeft;
int mKeyRight;
int mKeyCounterClockwise;
int mKeyClockwise;
	
//OGRE_SPECIFIC

//gui
OgreBites::Button* mJoinButton;

/***************************************
*			          METHODS
***************************************/

public:

//run
void run();

//time
float getRenderTime();

//scene
Ogre::SceneManager* getSceneManager      () { return mSceneMgr; }

private:

//connect
void sendConnect   ();

//shutdown
void shutdown();

//packets
void readPackets   ();

//Ticks
void readServerTick           (ByteBuffer* byteBuffer);

// Network
void runNetwork    (float msec);

//input
void processInput();

//graphics
bool runGraphics();
	
//graphics
void        createScene          ();

//gui	
void hideGui();
void loadJoinScreen();
void hideJoinScreen();
void initializeGui();

//rendering
virtual bool        frameRenderingQueued (const Ogre::FrameEvent& evt);

//input
void buttonHit             (OgreBites::Button *button);
bool mouseMoved            ( const OIS::MouseEvent &arg );

//command
void sendCommand   ();
};

#endif
