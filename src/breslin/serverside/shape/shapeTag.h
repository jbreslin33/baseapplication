#ifndef SHAPETAG_H
#define SHAPETAG_H

#include "shape.h"

class ShapeTag : public	Shape
{

public:
ShapeTag(unsigned int index, Game* game, Client* client, Vector3D* position, Vector3D* velocity, Vector3D* rotation, Ogre::Root* root,
	  bool animated, bool collidable, float collisionRadius, int meshCode, bool ai);
~ShapeTag();

//delta move command
virtual void buildDeltaMoveCommand(Message *mes);
virtual int  setFlag();
virtual void buildDeltaMoveMessage(int flags, Message* message);
};

#endif