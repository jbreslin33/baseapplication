#ifndef GAME_H
#define GAME_H

/***************************************
*   		INCLUDES
***************************************/
//standard library

//parents
#include "BaseApplication.h"

//command
#include "../../command/command.h"

/***************************************
*   		FORWARD DECLARATIONS
***************************************/
class Client;
class MovableTextOverlay;
class Dispatch;
class ShapeDynamic;
class Time;
class Network;

class Game : public BaseApplication
{
public:
	
	Game(const char* serverIP);
	~Game();

/***************************************
*   		MEMBER VARIABLES
***************************************/

	//Shapes
	std::vector<ShapeDynamic*> mShapeVector;	 //all shapes in the client world
	std::vector<ShapeDynamic*> mShapeGhostVector;	 //all shapes in the client world's ghost 

	std::vector<MovableTextOverlay*> myVect;  //for writing above shapes head

	//commands
	Command* mLastCommandToServer;
	Command* mCommandToServer; //for the human moves to be sent off to server

	// Dispatches
	static const char mCommandKey          = 1;
	static const char mCommandMilliseconds = 2;

	static const char mMessageFrame = 1;
	static const char mMessageConnect     = -101;
	static const char mMessageDisconnect  = -102;
	static const char mMessageAddShape    = -103;
	static const char mMessageRemoveShape = -104;

	static const char mMessageConnecting    = 0;
	static const char mMessageConnected     = 1;
	static const char mMessageDisconnecting = 2;
	static const char mMessageDisconnected  = 4;

	static const char mMessageNonDeltaFrame = 2;
	static const char mMessageServerExit = 3;
	static const char mMessageKeepAlive = 12;

	//Network
	Network*     mNetwork;
	int			 mServerPort;				// Port
	const char*  mServerIP;

	//time
	Time* mTime;
	float mFrameTime;
	float mRenderTime;
	int   mOldTime;
	
	//initialize
	bool mInit;
	bool mNetworkShutdown;
	bool mJoinGame;
	bool mPlayingGame;
	bool mInitializeGui;

	//gui
	OgreBites::Button* mJoinButton;

	//keys
	int mKeyUp;
	int mKeyDown;
	int mKeyLeft;
	int mKeyRight;
	int mKeySpace;

	/***************************************
			          METHODS
	***************************************/
	//Admin
	void shutdown();
	void gameLoop();

	//shape
	void addShape    (bool b, Dispatch* dispatch);
	void removeShape (Dispatch* dispatch);

	ShapeDynamic* getShapeDynamic      (  int id);

	void frame           (Dispatch* dispatch);
	void interpolateFrame();

	// Network
	void runNetwork    (int msec);
	void readPackets   ();
	void sendConnect   (const char *name);
	void sendDisconnect(void);
	void sendCommand   ();

	//input
	void processUnbufferedInput();
	void buttonHit             (OgreBites::Button *button);
	bool mouseMoved            ( const OIS::MouseEvent &arg );

	//graphics
	Ogre::SceneManager* getSceneManager      () { return mSceneMgr; }
    virtual void        createScene          ();
    virtual bool        frameRenderingQueued (const Ogre::FrameEvent& evt);
	bool                runGraphics          ();

	//gui	
	void hideGui();
	void loadJoinScreen();
	void hideJoinScreen();
	void unloadOtherScreens();
	void initializeGui();

	//time
	float getRenderTime() { return mRenderTime; }
	

};

#endif
