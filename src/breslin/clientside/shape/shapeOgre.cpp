#include "shapeOgre.h"

//standard library
#include <string.h>

//log
#include "../tdreamsock/dreamSockLog.h"

//application
#include "../game/applicationOgre.h"

//shape
#include "shape.h"

//ability
#include "../ability/animation/abilityAnimationOgre.h"

//title
#include "../billboard/objectTitle.h"

//math
#include "../../math/vector3D.h"


ShapeOgre::ShapeOgre(Shape* shape)
{
	//we use this to name shape. as ogre is picky about same names. it also serves as a counter of sorts.
	mShape = shape;
	mApplicationOgre = 0;
	//createShape(mShape->mPosition);

}

ShapeOgre::~ShapeOgre()
{
	delete mObjectTitle;
	//delete mEntity;
	delete mSceneNode;
}
