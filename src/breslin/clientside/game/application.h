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

private:

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

//Ticks
void readServerTick           (ByteBuffer* byteBuffer);

//shutdown
void shutdown();



private:

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

};

#endif
