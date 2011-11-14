#ifndef DYNAMICSHAPE_H
#define DYNAMICSHAPE_H

/***************************************
*           INCLUDES
***************************************/
//standard library
#include <vector>

//parent
#include "shape.h"

//command
#include "../command/command.h"

/***************************************
*           FORWARD DECLARATIONS
***************************************/

//game
class Game;

//byteBuffer
class ByteBuffer;

//ability
class Ability;

//parser
class Parser;

/**********************************
*          CLASS
**********************************/
class ShapeDynamic : public Shape
{

public:
ShapeDynamic(Game* game, ByteBuffer* byteBuffer);
~ShapeDynamic();

/************************************************
*                VARIABLES
*************************************************/


/*************************************************
*				METHODS
**************************************************/




};

#endif

