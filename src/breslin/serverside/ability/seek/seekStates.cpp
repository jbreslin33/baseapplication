//parent
#include "seekStates.h"

//log
#include "../../tdreamsock/dreamSockLog.h"

//states
#include "seekStateMachine.h"

//ability
#include "seek.h"

//server
#include "../../server/server.h"

//game
#include "../../game/game.h"

//shape
#include "../../shape/shape.h"

//vector3D
#include "../../../math/vector3D.h"

/*****************************************
	Normal_Seek
****************************************/
Normal_Seek* Normal_Seek::Instance()
{
  static Normal_Seek instance;
  return &instance;
}
void Normal_Seek::enter(Seek* seek)
{
	//LogString("Normal");
}
void Normal_Seek::execute(Seek* seek)
{
	if (seek->mSeekShape || seek->mSeekPoint)
	{
		//LogString("seeking");
		Vector3D* currentPosition;
		currentPosition->convertFromVector3(seek->mShape->mSceneNode->getPosition());
		
	}
	else
	{
		seek->mSeekStateMachine->changeState(No_Seek::Instance());
	}
/*
	//check for No_seek and Decelerate and Accelerate states..
    	if (seek->mShape->mKeyDirection.isZeroLength()) 
	{
		if(seek->mRunSpeed > 0.0) //Decelerate_Seek
		{
			seek->mSeekStateMachine->changeState(Decelerate_Seek::Instance());
			return;
		}
        	else //No_Seek
		{
			seek->mSeekStateMachine->changeState(No_Seek::Instance());
			return;
		}
    	}
	else 
	{
        	if(seek->mRunSpeed < seek->mShape->mSpeedMax) //Accelerate_Seek
		{
			seek->mSeekStateMachine->changeState(Accelerate_Seek::Instance());
			return;
		}
	}

	//actual seek
	seek->mShape->mSceneNode->translate(seek->mShape->mKeyDirection.x * seek->mShape->mGame->mServer->mFrameTime / 1000.0f * seek->mRunSpeed,
		0,
		seek->mShape->mKeyDirection.z  * seek->mShape->mGame->mServer->mFrameTime / 1000.0f * seek->mRunSpeed,
		Node::TS_WORLD);
*/
}
void Normal_Seek::exit(Seek* seek)
{
}

/*****************************************
	No_Seek
****************************************/
No_Seek* No_Seek::Instance()
{
	static No_Seek instance;
	return &instance;
}
void No_Seek::enter(Seek* seek)
{
	//LogString("No");
}
void No_Seek::execute(Seek* seek)
{
	if (seek->mSeekShape == NULL && seek->mSeekPoint == NULL)
	{
		//LogString("Not seeking");
	}
	else
	{
		seek->mSeekStateMachine->changeState(Normal_Seek::Instance());
	}
/*
	if (seek->mShape->mKeyDirection.isZeroLength()) 
	{
		if(seek->mRunSpeed > 0.0) //Decelerate_Seek
		{
			seek->mSeekStateMachine->changeState(Decelerate_Seek::Instance());
			return;
		}
        	else //No_Seek
		{
           		seek->mRunSpeed = 0.0;
		}
    	}
	else 
	{
        	if(seek->mRunSpeed < seek->mShape->mSpeedMax) //Accelerate_Seek
		{
			seek->mSeekStateMachine->changeState(Accelerate_Seek::Instance());
			return;
		}
		else //Normal_Seek 
		{
			seek->mSeekStateMachine->changeState(Normal_Seek::Instance());
			return;
		}
	}
*/
}
void No_Seek::exit(Seek* seek)
{
}

