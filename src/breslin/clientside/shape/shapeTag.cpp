//header
#include "shapeTag.h"

//log
#include "../tdreamsock/dreamSockLog.h"

//application
#include "../game/application.h"

//byteBuffer
#include "../bytebuffer/byteBuffer.h"

ShapeTag::ShapeTag(Application* application, ByteBuffer* byteBuffer, bool isGhost)
: Shape(application,byteBuffer,isGhost)
{
	
}
ShapeTag::~ShapeTag()
{
}

int ShapeTag::parseDeltaByteBuffer(ByteBuffer* byteBuffer)
{
	int flags = Shape::parseDeltaByteBuffer(byteBuffer);
	if(flags & mCommandIt)
	{
		appendToTitle("IT");
		if (mLocal == 1)
		{
			LogString("localHH");
		}
	}
	return flags;
}


