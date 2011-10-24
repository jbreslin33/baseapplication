#ifndef SHAPETAG_H
#define SHAPETAG_H

#include "shape.h"

class ShapeTag : public	Shape
{

public:
ShapeTag(Game* game, Client* client, Vector3D* position, Vector3D* velocity, Vector3D* rotation, Ogre::Root* root,unsigned int index,
	  bool animated, bool collidable, float collisionRadius, int meshCode, bool ai);
~ShapeTag();


};

#endif