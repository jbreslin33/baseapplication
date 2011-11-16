#include "command.h"

Command::Command()
{
	mPosition         = new Vector3D();
	mMoveVelocity     = new Vector3D();

	mRotation        = new Vector3D();
	mRotSpeed = 0.0f;

	mMilliseconds = 0;
}

Command::~Command()
{
}
