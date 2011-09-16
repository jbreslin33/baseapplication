#include "rotationStates.h"
#include "rotationStateMachine.h"

#include "rotation.h"

#define TURN_SPEED 250.0f      // character turning in degrees per second

Normal_Rotation* Normal_Rotation::Instance()
{
  static Normal_Rotation instance;
  return &instance;
}
void Normal_Rotation::enter(Rotation* rotation)
{
}
void Normal_Rotation::execute(Rotation* rotation)
{
	if (rotation->mKeyRotation == 0)
	{
		rotation->mRotationStateMachine->changeState(No_Rotation::Instance());
		return;
	}

	float clientFrametime;

    clientFrametime = rotation->mCommand.mMilliseconds / 1000.0f;;


	rotation->mSceneNode->yaw(Degree(rotation->mKeyRotation * clientFrametime * TURN_SPEED), Node::TS_WORLD);

	//rotation->mGoalDirection = Vector3::ZERO;   // we will calculate this

	//Real yawAtSpeed;

	//rotation->mSceneNode->yaw(Degree(yawToGoal));
}
void Normal_Rotation::exit(Rotation* rotation)
{
}

Accelerate_Rotation* Accelerate_Rotation::Instance()
{
  static Accelerate_Rotation instance;
  return &instance;
}
void Accelerate_Rotation::enter(Rotation* rotation)
{
}
void Accelerate_Rotation::execute(Rotation* rotation)
{
	if (rotation->mCommand.mKey != 0)
	{
		rotation->mRotationStateMachine->changeState(Normal_Rotation::Instance());
		return;
	}
}
void Accelerate_Rotation::exit(Rotation* rotation)
{
}

Decelerate_Rotation* Decelerate_Rotation::Instance()
{
  static Decelerate_Rotation instance;
  return &instance;
}
void Decelerate_Rotation::enter(Rotation* rotation)
{
}
void Decelerate_Rotation::execute(Rotation* rotation)
{
	if (rotation->mCommand.mKey != 0)
	{
		rotation->mRotationStateMachine->changeState(Normal_Rotation::Instance());
		return;
	}
}
void Decelerate_Rotation::exit(Rotation* rotation)
{
}


No_Rotation* No_Rotation::Instance()
{
  static No_Rotation instance;
  return &instance;
}
void No_Rotation::enter(Rotation* rotation)
{
}
void No_Rotation::execute(Rotation* rotation)
{
	if (rotation->mCommand.mKey != 0)
	{
		rotation->mRotationStateMachine->changeState(Normal_Rotation::Instance());
		return;
	}
}
void No_Rotation::exit(Rotation* rotation)
{
}

