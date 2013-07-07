#include "rotationStates.h"

//log
#include "../../tdreamsock/dreamSockLog.h"

//states
#include "rotationStateMachine.h"

//ability
#include "rotation.h"

//server
#include "../../server/server.h"

//game
#include "../../game/game.h"

//shape
#include "../../shape/shape.h"

#define MAX_TURN_SPEED 100     // character turning in degrees per second

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
	
	if (rotation->mDegrees == 0)
	{
		if(rotation->mRotationSpeed > 0.0) //Decelerate_Rotation
		{
			rotation->mRotationStateMachine->changeState(Decelerate_Rotation::Instance());
			return;
		}
        else //No_Rotation
		{
			rotation->mRotationStateMachine->changeState(No_Rotation::Instance());
			return;
		}
	}
	else
	{
		if(rotation->mRotationSpeed < MAX_TURN_SPEED) //Accelerate_Rotation
		{
			rotation->mRotationStateMachine->changeState(Accelerate_Rotation::Instance());
			return;
		}
	}

	//actual rotate
//	LogString("N:%f",rotation->mRotationSpeed);
	rotation->mShape->mSceneNode->yaw(Degree(rotation->mDegrees * rotation->mShape->mGame->mServer->mFrameTime / 1000.0f * rotation->mRotationSpeed), Node::TS_WORLD);

//rotation->mShape->mSceneNode->yaw(Degree(rotation->mDegrees * rotation->mShape->mClientFrametime * MAX_TURN_SPEED), Node::TS_WORLD);
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
	/*
	if (rotation->mShape->mKey != 0)
	{
		rotation->mRotationStateMachine->changeState(Normal_Rotation::Instance());
		return;
	}
	*/
	if (rotation->mDegrees == 0)
	{
		if(rotation->mRotationSpeed > 0.0) //Decelerate_Rotation
		{
			rotation->mRotationStateMachine->changeState(Decelerate_Rotation::Instance());
			return;
		}
        else //No_Rotation
		{
			rotation->mRotationStateMachine->changeState(No_Rotation::Instance());
			return;
		}
    }
	else 
	{
        if(rotation->mRotationSpeed < MAX_TURN_SPEED) //Accelerate_Rotation
		{
			rotation->mRotationSpeed += rotation->mRotationAccel;
		}
		else //Normal_Rotation 
		{
			rotation->mRotationStateMachine->changeState(Normal_Rotation::Instance());
			return;
		}
	}

	//actual rotate
//	LogString("A:%f",rotation->mRotationSpeed);
	rotation->mShape->mSceneNode->yaw(Degree(rotation->mDegrees * rotation->mShape->mGame->mServer->mFrameTime / 1000.0f * rotation->mRotationSpeed), Node::TS_WORLD);
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
	/*
	if (rotation->mShape->mKey != 0)
	{
		rotation->mRotationStateMachine->changeState(Normal_Rotation::Instance());
		return;
	}
	*/
	if (rotation->mDegrees == 0)
	{
		if(rotation->mRotationSpeed > 0.0) //Decelerate_Rotation
		{
			rotation->mRotationSpeed -= rotation->mRotationDecel;
		}
        else //No_Rotation
		{
			rotation->mRotationStateMachine->changeState(No_Rotation::Instance());
			return;
		}
    }
	else 
	{
        if(rotation->mRotationSpeed < MAX_TURN_SPEED) //Accelerate_Rotation
		{
			rotation->mRotationStateMachine->changeState(Accelerate_Rotation::Instance());
			return;
		}
		else //Normal_Rotation 
		{
			rotation->mRotationStateMachine->changeState(Normal_Rotation::Instance());
			return;
		}
	}

//	LogString("D:%f",rotation->mRotationSpeed);
	//actual rotate
	rotation->mShape->mSceneNode->yaw(Degree(rotation->mDegrees * rotation->mShape->mGame->mServer->mFrameTime / 1000.0f * rotation->mRotationSpeed), Node::TS_WORLD);

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
	if (rotation->mDegrees == 0)
	{
		if(rotation->mRotationSpeed > 0.0) //Decelerate_Rotation
		{
			rotation->mRotationStateMachine->changeState(Decelerate_Rotation::Instance());
			return;
		}
        else //No_Rotation
		{
           rotation->mRotationSpeed = 0.0;
		}
    }
	else 
	{
        if(rotation->mRotationSpeed < MAX_TURN_SPEED) //Accelerate_Rotation
		{
			rotation->mRotationStateMachine->changeState(Accelerate_Rotation::Instance());
			return;
		}
		else //Normal_Rotation
		{
			rotation->mRotationStateMachine->changeState(Normal_Rotation::Instance());
			return;
		}
	}
}
void No_Rotation::exit(Rotation* rotation)
{
}

