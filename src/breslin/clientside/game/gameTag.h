#ifndef GAMETAG_H
#define GAMETAG_H
/**************************************
@GameTag: This class just extends Game and right now just overides addShape to create a 
shapeTag instance.

*************************************/

/************************************
			HEADERS
************************************/
//parent
#include "game.h"

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

class GameTag : public Game
{
public:
	
	GameTag(Application* application);
	~GameTag();

/***************************************
*   		MEMBER VARIABLES
***************************************/
public:

private:

/***************************************
*			          METHODS
***************************************/
public:

//shape
virtual void   addShape       (bool b, ByteBuffer* byteBuffer);

};

#endif
