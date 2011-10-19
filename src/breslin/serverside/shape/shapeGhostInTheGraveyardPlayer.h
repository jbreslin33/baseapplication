#ifndef SHAPEGHOSTINTHEGRAVEYARDPLAYER_H
#define SHAPEGHOSTINTHEGRAVEYARDPLAYER_H

#include "shape.h"

class ShapeGhostInTheGraveyardPlayer : public Shape
{

public:
ShapeGhostInTheGraveyardPlayer(Vector3D* position, Vector3D* velocity, Vector3D* rotation, Ogre::Root* root,unsigned int index,
	  bool animated, bool collidable, float collisionRadius, int meshCode, bool ai);
~ShapeGhostInTheGraveyardPlayer();


};

#endif