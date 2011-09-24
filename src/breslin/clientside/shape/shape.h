#ifndef SHAPE_H
#define SHAPE_H

/**********************************
*          INCLUDES
**********************************/
//standard library
#include <string>

//math
#include "../../math/vector3D.h"

/**********************************
*          FORWARD DECLARATIONS
**********************************/
class Game;
class Parser;

class Shape
{
public:

Shape();
~Shape();

/**************************************************
*			VARIABLES
**************************************************/
public:

//id
int   mIndex;

//game
Game* mGame;

//scale
float mScale;

Parser* mParser;

/**************************************************
*			METHODS
**************************************************/

//setting position
virtual void     setPosition          (Vector3D                  ) = 0;
virtual void     setPosition          (float x, float y, float z ) = 0;

//setting rotation
virtual void    setRotation(Vector3D* vector3D) = 0;

//getting position
virtual Vector3D* getPosition          (                          ) = 0;
virtual Vector3D* getRotation          (                          ) = 0;
//size
virtual void     scale                (Vector3D                  ) = 0;

//visibility
virtual void     setVisible           (bool b                    ) = 0;


//title
virtual void     drawTitle            (                          ) = 0;
virtual void     appendToTitle        (std::string appendage     ) = 0;
virtual void     appendToTitle        (int appendage             ) = 0;
virtual void     clearTitle           (                          ) = 0;

};

#endif
