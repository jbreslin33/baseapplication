#ifndef COMMAND_H
#define COMMAND_H

#include "../../math/vector3D.h"

class Command
{
public:
Command();
~Command();
	
Vector3D* mPosition;      //finish origin of frame/tick
Vector3D* mPositionOld;   //origin of last frame/tick
Vector3D* mMoveVelocity;	//velocity during frame/tick

Vector3D* mRot;         //rotation during frame/tick
Vector3D* mRotOld;	    //velocity during last frame/tick
Vector3D* mRotationVelocity;

float mRotSpeed;

int mKey;               //key pressed
int mMilliseconds;      //not used
int mMillisecondsTotal;      //not used

float mClientFrametime;
};
#endif
