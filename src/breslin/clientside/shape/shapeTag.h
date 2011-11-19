#ifndef SHAPETAG_H
#define SHAPETAG_H

/**********************************
*          INCLUDES
**********************************/
//parent
#include "shape.h"

/**********************************
*          FORWARD DECLARATIONS
**********************************/

class ShapeTag : public Shape
{
public:

ShapeTag(Application* application, ByteBuffer* byteBuffer, bool isGhost);
~ShapeTag();

/**************************************************
*			VARIABLES
**************************************************/
public:

private:
	static const char mCommandIt   = 128;

/**************************************************
*			METHODS
**************************************************/

protected:
virtual int parseDeltaByteBuffer(ByteBuffer *mes);

};

#endif
