#ifndef COMMAND_H
#define COMMAND_H

#include "../../math/vector3D.h"

class Command
{
public:
Command();
~Command();
	
Vector3D* mPosition;      //finish origin of frame/tick
Vector3D* mRotation;         //rotation during frame/tick
int mFrameTime;      //not used

};
#endif
