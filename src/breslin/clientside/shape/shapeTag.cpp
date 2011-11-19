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
	LogString("Check for IT");
	int flags = Shape::parseDeltaByteBuffer(byteBuffer);
	if(flags & mCommandIt)
	{
		LogString("IT");
		appendToTitle("IT");
	}
	return flags;
}


