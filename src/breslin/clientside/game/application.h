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

//Shapes
std::vector<ShapeDynamic*> mShapeVector;	 //all shapes in the client world
std::vector<ShapeDynamic*> mShapeGhostVector;	 //all shapes in the client world's ghost 

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
void gameLoop();

//shape
virtual void          addShape       (bool b, ByteBuffer* byteBuffer);
        void          removeShape    (ByteBuffer* byteBuffer);
        ShapeDynamic* getShapeDynamic(int id);

//Ticks
void readServerTick           (ByteBuffer* byteBuffer);
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
