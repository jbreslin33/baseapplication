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
	
	
/***************************************
*			          METHODS
***************************************/

//Admin
void shutdown();
virtual void gameLoop();

//Ticks
virtual void readServerTick           (ByteBuffer* byteBuffer);


//time
virtual float getRenderTime() {  return 0; }

private:

// Network
void runNetwork    (float msec);

//input
virtual void processInput() { }

//graphics
virtual bool runGraphics() { return false; }
	

//graphics
//Ogre::SceneManager* getSceneManager      () { return mSceneMgr; }
virtual void        createScene          () { }
//virtual bool        frameRenderingQueued (const Ogre::FrameEvent& evt);

//gui	
virtual void hideGui() { }
virtual void loadJoinScreen() { }
virtual void hideJoinScreen() { }
virtual void unloadOtherScreens() { }
virtual void initializeGui() { };

	//input
//void buttonHit             (OgreBites::Button *button);
//bool mouseMoved            ( const OIS::MouseEvent &arg );

//shape stuff...
virtual Vector3D* getRotation(Shape* shapeDynamic) { return 0; }
virtual void createShape() { }

};

#endif
