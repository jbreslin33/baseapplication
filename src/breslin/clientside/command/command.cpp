#include "command.h"

Command::Command()
{
	mPosition = new Vector3D();
	mVelocity = new Vector3D();
	mRotation = new Vector3D();

	mRotationSpeed = 0.0f;

	mMilliseconds = 0;
}

Command::~Command()
{
}
