#include "ogreShape.h"
#include "../tdreamsock/dreamSockLog.h"

//math
#include "../../math/vector3D.h"

#include "shape.h"

OgreShape::OgreShape()
{
}

//this is the contructor for server side ogre shape
OgreShape::OgreShape(unsigned int index, Vector3D* position, Vector3D* velocity, Vector3D* rotation, Ogre::Root* root)
{
	
}

OgreShape::~OgreShape()
{
	//delete mSceneManager;
	//delete mSceneNode;
}
