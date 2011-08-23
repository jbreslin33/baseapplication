#ifndef GAME_H
#define GAME_H

/***************************************
*   		INCLUDES
***************************************/
//standard library
#include <vector>

//parents

/***************************************
*   		FORWARD DECLARATIONS
***************************************/
class Client;
class Dispatch;
class ShapeDynamic;
class Time;
class Network;
class Parser;
class Command;

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

//Network
Network*     mNetwork;

//time
Time* mTime;
float mFrameTime;
int   mOldTime;

//parser
Parser* mParser;

	
/***************************************
*			          METHODS
***************************************/

//Admin
void shutdown();
void gameLoop();

//shape
virtual void          addShape       (bool b, Dispatch* dispatch);
        void          removeShape    (Dispatch* dispatch);
        ShapeDynamic* getShapeDynamic(int id);

//Ticks
void readServerTick           (Dispatch* dispatch);
void interpolateTick();

//time
virtual float getRenderTime() {  return 0; }

private:

// Network
void runNetwork    (float msec);

//input
virtual void processInput() { }

//graphics
virtual bool runGraphics() { return false; }
	
};

#endif
