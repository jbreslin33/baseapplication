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
Vector3D mPosition;            //finish origin of frame/tick
Vector3D mPositionOld;            //origin of last frame/tick
Vector3D mPositionVelocity;	         //velocity during frame/tick

Vector3D mRotation; //rotation during frame/tick
Vector3D mRotationOld;	//velocity during last frame/tick
Vector3D mRotationVelocity;
float mRotSpeed;

int mKey;               //key pressed
int mMilliseconds;      //not used
int mMillisecondsTotal;      //not used

float mClientFrametime;

/******************************************************
*				METHODS
********************************************************/
};
#endif
