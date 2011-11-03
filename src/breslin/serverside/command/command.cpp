#include "command.h"

Command::Command()
{
	mPosition         = new Vector3D();
	mPositionOld      = new Vector3D();
	mPositionVelocity = new Vector3D();

	mRotation         = new Vector3D();

	mKey = 0;

	mMilliseconds = 19;
	mMillisecondsTotal = 0;

	mClientFrametime = 0.0f;
}

Command::~Command()
{
}

