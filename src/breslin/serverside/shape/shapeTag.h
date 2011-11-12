#ifndef SHAPETAG_H
#define SHAPETAG_H

#include "shape.h"

class ShapeTag : public	Shape
{

public:
ShapeTag(unsigned int index, Game* game, Client* client, Vector3D* position, Vector3D* velocity, Vector3D* rotation, Ogre::Root* root,
	  bool animated, bool collidable, float collisionRadius, int meshCode, bool ai);
~ShapeTag();

int setFlag();
virtual void addToMoveMessage(Message* message);

};

#endif