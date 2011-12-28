#include "command.h"

Command::Command()
{
	mPosition = new Vector3D();
	mRotation = new Vector3D();

	mFrameTime = 0;
}

Command::~Command()
{
}
