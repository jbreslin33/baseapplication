#include "command.h"

Command::Command()
{
	mPosition = new Vector3D();
	mVelocity = new Vector3D();
	mRotation = new Vector3D();

	mMilliseconds = 0;
}

Command::~Command()
{
}
