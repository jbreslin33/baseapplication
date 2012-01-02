#ifndef GAME_H
#define GAME_H
/**************************************
@Game: This class should handle game specific duties. It should be able to be destroyed without
the applicationBreslin crashing. You should be able to switch games while the applicationBreslin is running.

Since this is on the client side it does not need any game logic.

It's main duties will be to track objects to be drawn(Shapes). When it is destroyed or
reset these objects need to be destroyed.

*************************************/


/***************************************
*   		INCLUDES
***************************************/
//standard library
#include <vector>

/***************************************
*   		FORWARD DECLARATIONS
***************************************/
class ApplicationBreslin;
class ByteBuffer;
class Shape;
class StateMachine;
class State;

class Game 
{
public:
	
	Game(ApplicationBreslin* applicationBreslin);
	~Game();

/***************************************
*   		MEMBER VARIABLES
***************************************/
public:

//states
StateMachine* mStateMachine;

State* mGameGlobal;
State* mGameInitialize;
State* mGamePlay;
State* mGamePause;


// constants
static const char mCommandKey          = 1;
static const char mCommandFrameTime = 2;

static const char mMessageFrame = 1;

static const char mMessageAddShape    = -103;
static const char mMessageRemoveShape = -104;

protected:

//applicationBreslin
ApplicationBreslin* mApplicationBreslin;

//Shapes
std::vector<Shape*>* mShapeVector;	 //all shapes in the client world
std::vector<Shape*>* mShapeGhostVector;	 //all shapes in the client world's ghost 

//keys
int mKeyUp;
int mKeyDown;
int mKeyLeft;
int mKeyRight;
int mKeyCounterClockwise;
int mKeyClockwise;
	
//key input
int mKeyCurrent;   
int mKeyLast;

//sequences
signed short	mOutgoingSequence;

//time
float mRunNetworkTime;

/***************************************
*			          METHODS
***************************************/
public:

//update
void processUpdate();

//network
void sendByteBuffer();
void checkForByteBuffer();

//input
void processInput();



private:

//shape
virtual void addShape       (bool b, ByteBuffer* byteBuffer);
void removeShape    (ByteBuffer* byteBuffer);
Shape* getShape(int id);

//network

void readServerTick(ByteBuffer* byteBuffer);
void sendCommand();
};

#endif
