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
//Ogre
#include <OgreEntity.h>


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
	
	Game(ApplicationBreslin* application);
	~Game();

/***************************************
*   		MEMBER VARIABLES
***************************************/
public:

//states
StateMachine* mStateMachine;

State* mGamePlay;

// constants
static const char mMessageKey       = 1;
static const char mMessageFrameTime = 2;

static const char mMessageFrame = 1;

static const char mMessageAddShape    = -103;
static const char mMessageRemoveShape = -104;
static const char mMessageSetText     = -66;

static const char mMessageQuitGame = -108;


//applicationBreslin
ApplicationBreslin* mApplication;

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

public:
float mFrameTimeServer;

//scene
Ogre::Light* mPointLight;

Ogre::Entity* mFloor;
Ogre::SceneNode* mFloorNode;

Ogre::Entity* mNorthWall;
Ogre::SceneNode* mNorthWallNode;

/***************************************
*			          METHODS
***************************************/
public:

//states
virtual void createStates();
virtual void setStates();

void remove();

//update
virtual void processUpdate();

//network
virtual void sendByteBuffer();
virtual void checkByteBuffer(ByteBuffer* byteBuffer);

private:

//shape
virtual void addShape       (ByteBuffer* byteBuffer);
void removeShape    (ByteBuffer* byteBuffer);
Shape* getShape(int id);

//scene
void createScene();

//network

void readServerTick(ByteBuffer* byteBuffer);
void sendCommand();
};

#endif
