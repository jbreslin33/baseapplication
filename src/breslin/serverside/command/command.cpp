#include "command.h"

Command::Command()
{
	mPosition.x = 0.0;
	mPosition.y = 0.0;
	mPosition.z = 0.0;

	mPositionOld.x = 0.0;
	mPositionOld.y = 0.0;
	mPositionOld.z = 0.0;

	mPositionVelocity.x = 0.0;
	mPositionVelocity.y = 0.0;
	mPositionVelocity.z = 0.0;

	mRotation.x = 0.0;
	mRotation.y = 0.0;
	mRotation.z = 0.0;

	mRotationOld.x = 0.0;
	mRotationOld.y = 0.0;
	mRotationOld.z = 0.0;

	mRotationVelocity.x = 0.0;
	mRotationVelocity.y = 0.0;
	mRotationVelocity.z = 0.0;

	mKey = 0;
	mMilliseconds = 19;
	mMillisecondsTotal = 0;
	mClientFrametime = 0.0f;
}

Command::~Command()
{
}
