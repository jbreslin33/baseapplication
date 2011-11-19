#ifndef GAME_H
#define GAME_H
/**************************************
@Game: This class should handle game specific duties. It should be able to be destroyed without
the application crashing. You should be able to switch games while the application is running.

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
class Application;
class ByteBuffer;
class Shape;

class Game 
{
public:
	
	Game(Application* application, const char* serverIP, int serverPort);
	~Game();

/***************************************
*   		MEMBER VARIABLES
***************************************/
private:
//application
Application* mApplication;

//Shapes
std::vector<Shape*> mShapeVector;	 //all shapes in the client world
std::vector<Shape*> mShapeGhostVector;	 //all shapes in the client world's ghost 

	
/***************************************
*			          METHODS
***************************************/
public:

//shape
void   addShape       (bool b, ByteBuffer* byteBuffer);
void   removeShape    (ByteBuffer* byteBuffer);
Shape* getShape(int id);

void run();

};

#endif
