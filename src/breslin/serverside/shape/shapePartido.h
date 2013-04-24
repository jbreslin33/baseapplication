#ifndef SHAPEPARTIDO_H
#define SHAPEPARTIDO_H
/******************************************
*            INCLUDES
****************************************/

#include "shape.h"

/******************************************
*            FORWARD DECLARATIONS
****************************************/
class GamePartido;
/******************************************
*            CLASS
****************************************/
class ShapePartido : public	Shape
{

public:
ShapePartido(unsigned int index, GamePartido* gamePartido, Client* client, Vector3D* position, Vector3D* velocity, Vector3D* rotation, Ogre::Root* root,
	  bool animated, bool collidable, float collisionRadius, int meshCode, bool ai);
~ShapePartido();

/******************************************
*            VARIABLES
****************************************/

GamePartido* mGamePartido;
bool mInBattle;

/******************************************
*            METHODS
****************************************/
void processTick();
};

#endif