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
class ClientPartido;
/******************************************
*            CLASS
****************************************/
class ShapePartido : public Shape
{

public:
ShapePartido(unsigned int index, GamePartido* gamePartido, ClientPartido* clientPartido, Vector3D* position, Vector3D* velocity, Vector3D* rotation, Ogre::Root* root,
	  bool animated, bool collidable, float collisionRadius, int meshCode, bool ai);
~ShapePartido();

/******************************************
*            VARIABLES
****************************************/
GamePartido*   mGamePartido;
ClientPartido* mClientPartido;
Shape*  mOpponent;

/******************************************
*            METHODS
****************************************/
virtual void processTick();
virtual void collision(Shape* shape);

};

#endif
