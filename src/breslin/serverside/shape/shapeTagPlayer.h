#ifndef SHAPETAGPLAYER_H
#define SHAPETAGPLAYER_H

#include "shapeTag.h"

class ShapeTagPlayer : public ShapeTag
{

public:
ShapeTagPlayer(unsigned int index, Game* game, Client* client, Vector3D* position, Vector3D* velocity, Vector3D* rotation, Ogre::Root* root,
	  bool animated, bool collidable, float collisionRadius, int meshCode, bool ai);
~ShapeTagPlayer();

bool mIt;

};

#endif