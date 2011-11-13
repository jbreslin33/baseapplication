#ifndef SHAPEDYNAMICOGRETAG_H
#define SHAPEDYNAMICOGRETAG_H

/**********************************
*          INCLUDES
**********************************/
//parent
#include "shapeOgre.h"

/**********************************
*          FORWARD DECLARATIONS
**********************************/

//gameOgre
class GameOgre;

//ByteBuffer
class ByteBuffer;

/**********************************
*          CLASS
**********************************/
class ShapeOgreTag : public ShapeOgre
{

public:
ShapeOgreTag(GameOgre* gameOgre, ByteBuffer* byteBuffer, bool isGhost);
~ShapeOgreTag();

/**********************************
*          VARIABLES
**********************************/


/**********************************
*          METHODS
**********************************/


};

#endif

