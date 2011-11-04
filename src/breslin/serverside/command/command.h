#ifndef COMMAND_H
#define COMMAND_H

/******************************************************
*				INCLUDES
********************************************************/
#include "../../math/vector3D.h"

/******************************************************
*				FORWARD DECLARATIONS
********************************************************/

/******************************************************
*				CLASS
********************************************************/
class Command
{
public:
Command();
~Command();

/******************************************************
*				VARIABLES
********************************************************/
Vector3D* mPosition;            //finish origin of frame/tick
Vector3D* mPositionBeforeCollision;            //origin of last frame/tick
Vector3D* mPositionVelocity;	         //velocity during frame/tick

Vector3D* mRotation; //rotation during frame/tick

int mKey;               //key pressed

int mMilliseconds;      //not used
int mMillisecondsTotal;      //not used

float mClientFrametime;

/******************************************************
*				METHODS
********************************************************/
};
#endif
