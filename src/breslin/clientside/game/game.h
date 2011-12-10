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

//applicationBreslin
ApplicationBreslin* mApplicationBreslin;


StateMachine* mStateMachine;

State* mGameGlobal;
State* mGameInitialize;
State* mGamePlay;
State* mGamePause;

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
int mMillisecondsCurrent;
int mMillisecondsLast; 
	
/***************************************
*			          METHODS
***************************************/
public:

//shape
virtual void   addShape       (bool b, ByteBuffer* byteBuffer);
void   removeShape    (ByteBuffer* byteBuffer);
Shape* getShape(int id);
//input
void processInput();

void run();

};

#endif
