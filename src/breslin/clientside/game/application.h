#ifndef APPLICATION_H
#define APPLICATION_H

/***************************************
*   		INCLUDES
***************************************/

//parents
#include "../game/BaseApplication.h"

//standard library
#include <vector>

/***************************************
*   		FORWARD DECLARATIONS
***************************************/
class Game;
class Client;
class ByteBuffer;
class Shape;
class Time;
class Network;
class Parser;
class Command;
class Vector3D;

class Application : public BaseApplication
{
public:
	
	Application(const char* serverIP, int serverPort);
	~Application();

/***************************************
*   		MEMBER VARIABLES
***************************************/
//game
Game* mGame;

//Network
Network*     mNetwork;

//time
Time* mTime;
float mFrameTime;
int   mOldTime;


//initialize
bool mInitializeGui;
bool mJoinGame;
bool mPlayingGame;

//game
Application* mApplication;

//time
float mRenderTime;

//gui
//OgreBites::Button* mJoinButton;

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

//Admin
void shutdown();
void gameLoop();

//Ticks
void readServerTick           (ByteBuffer* byteBuffer);


//time
float getRenderTime();

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
void unloadOtherScreens();
void initializeGui();

//shape stuff...
Vector3D* getRotation(Shape* shapeDynamic);
void createShape();

//OGRE_SPECIFIC

//graphics
Ogre::SceneManager* getSceneManager      () { return mSceneMgr; }
virtual bool        frameRenderingQueued (const Ogre::FrameEvent& evt);

//input
void buttonHit             (OgreBites::Button *button);
bool mouseMoved            ( const OIS::MouseEvent &arg );

};

#endif
