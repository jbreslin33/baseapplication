#include "command.h"

Command::Command()
{
	mPosition         = new Vector3D();
	mPositionOld      = new Vector3D();
	mMoveVelocity     = new Vector3D();

	mRot        = new Vector3D();
	mRotOld      = new Vector3D();

	mKey = 0;
	mMilliseconds = 0;
	mMillisecondsTotal = 0;
	mClientFrametime = 0.0f;
}

Command::~Command()
{
}
