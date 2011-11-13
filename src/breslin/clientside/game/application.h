#ifndef APPLICATION_H
#define APPLICATION_H

/***************************************
*   		INCLUDES
***************************************/
//standard library
#include <vector>

//parents

/***************************************
*   		FORWARD DECLARATIONS
***************************************/
class Game;
class Client;
class ByteBuffer;
class ShapeDynamic;
class Time;
class Network;
class Parser;
class Command;

class Application 
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
	
};

#endif
