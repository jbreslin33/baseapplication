//header
#include "shape.h"

//log
#include "../tdreamsock/dreamSockLog.h"

//parser
#include "../parser/parser.h"

Shape::Shape()
{
	mIndex = 0;
	mParser = new Parser();
}
Shape::~Shape()
{
}
