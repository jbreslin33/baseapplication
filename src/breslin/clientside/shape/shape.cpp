//header
#include "shape.h"

//log
#include "../tdreamsock/dreamSockLog.h"

//parser
#include "../parser/parser.h"

Shape::Shape()
{
	//id
	mIndex = 0;

	//scale
	mScale = 0;

	mParser = new Parser();
}
Shape::~Shape()
{
}
