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
class Dispatch;
class ShapeDynamic;
class Time;
class Network;
class Parser;

class Game 
{
public:
	
	Game(const char* serverIP, int serverPort);
	~Game();

/***************************************
*   		MEMBER VARIABLES
***************************************/

//Shapes
std::vector<ShapeDynamic*> mShapeVector;	 //all shapes in the client world
std::vector<ShapeDynamic*> mShapeGhostVector;	 //all shapes in the client world's ghost 

//commands
Command* mLastCommandToServer;
Command* mCommandToServer; //for the human moves to be sent off to server

//Network
Network*     mNetwork;

//time
Time* mTime;
float mFrameTime;
int   mOldTime;

//initialize
bool mInit;
bool mNetworkShutdown;

//parser
Parser* mParser;

	
/***************************************
*			          METHODS
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
