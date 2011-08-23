//header
#include "shape.h"

//log
#include "../tdreamsock/dreamSockLog.h"

//parser
#include "../parser/parser.h"

Shape::Shape(int ind, Vector3D* position, Vector3D* rotation)
{
	mIndex = ind;
	mParser = new Parser();
}
Shape::Shape()
{
	mIndex = 0;
}
Shape::~Shape()
{
}
