#ifndef GAME_H
#define GAME_H

/***************************************
*   		INCLUDES
***************************************/
//standard library
#include <vector>

//parents

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

class Game 
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
	int   mOldTime;

//initialize
bool mInit;
bool mNetworkShutdown;



	
	/***************************************
			          METHODS
	***************************************/
	//Admin
	void shutdown();
	void gameLoop();

	//shape
	virtual void addShape    (bool b, Dispatch* dispatch);
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

	//time
	virtual float getRenderTime() {  return 0; }

	//input
	virtual void processUnbufferedInput() { }

	//graphics
	virtual bool runGraphics() { return false; }
	
	virtual void initializeGui() { }

};

#endif
