#ifndef SHAPEDYNAMICOGRETAG_H
#define SHAPEDYNAMICOGRETAG_H

/**********************************
*          INCLUDES
**********************************/
//parent
#include "shapeDynamicOgre.h"

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
class ShapeDynamicOgreTag : public ShapeDynamicOgre
{

public:
ShapeDynamicOgreTag(GameOgre* gameOgre, ByteBuffer* byteBuffer, bool isGhost);
~ShapeDynamicOgreTag();

/**********************************
*          VARIABLES
**********************************/


/**********************************
*          METHODS
**********************************/


};

#endif

