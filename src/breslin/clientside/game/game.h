#ifndef GAME_H
#define GAME_H

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
//application
Application* mApplication;

//Shapes
std::vector<Shape*> mShapeVector;	 //all shapes in the client world
std::vector<Shape*> mShapeGhostVector;	 //all shapes in the client world's ghost 

	
/***************************************
*			          METHODS
***************************************/
//shape
virtual void          addShape       (bool b, ByteBuffer* byteBuffer) { }
        void          removeShape    (ByteBuffer* byteBuffer);
        Shape* getShape(int id);

void interpolateTick();

};

#endif
