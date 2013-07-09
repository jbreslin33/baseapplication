//parent
#include "seekStates.h"

//log
#include "../../tdreamsock/dreamSockLog.h"

//seek
#include "../seek.h"

//server
#include "../../server/server.h"

//game
#include "../../game/game.h"

//shape
#include "../../shape/shape.h"

//vector3D
#include "../../../math/vector3D.h"

//move
#include "../../move/move.h"

/*****************************************
*******       GLOBAL    ******************
****************************************/
GlobalSeek* GlobalSeek::Instance()
{
  static GlobalSeek instance;
  return &instance;
}
void GlobalSeek::enter(Seek* seek)
{
}
void GlobalSeek::execute(Seek* seek)
{

}
void GlobalSeek::exit(Seek* seek)
{
}
bool GlobalSeek::onMessage(Seek* seek, const Telegram& msg)
{
        return true;
}


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
 		Vector3D* newKeyDirection = new Vector3D();
                Vector3D* currentPosition  = new Vector3D();

                currentPosition->x = seek->mShape->mSceneNode->getPosition().x;
                currentPosition->y = seek->mShape->mSceneNode->getPosition().y;
                currentPosition->z = seek->mShape->mSceneNode->getPosition().z;

                newKeyDirection->subtract(seek->mSeekPoint,currentPosition);
                seek->mShape->mMove->mHeading->x = newKeyDirection->x;
               	seek->mShape->mMove->mHeading->y = newKeyDirection->y;
                seek->mShape->mMove->mHeading->z  = newKeyDirection->z;

                seek->mShape->mMove->mHeading->normalise();
	}
	else
	{
//		seek->mStateMachine->changeState(No_Seek::Instance());
	}
/*
	//check for No_seek and Decelerate and Accelerate states..
    	if (seek->mShape->mHeading.isZeroLength()) 
	{
		if(seek->mRunSpeed > 0.0) //Decelerate_Seek
		{
			seek->mStateMachine->changeState(Decelerate_Seek::Instance());
			return;
		}
        	else //No_Seek
		{
			seek->mStateMachine->changeState(No_Seek::Instance());
			return;
		}
    	}
	else 
	{
        	if(seek->mRunSpeed < seek->mShape->mSpeedMax) //Accelerate_Seek
		{
			seek->mStateMachine->changeState(Accelerate_Seek::Instance());
			return;
		}
	}

	//actual seek
	seek->mShape->mSceneNode->translate(seek->mShape->mHeading.x * seek->mShape->mGame->mServer->mFrameTime / 1000.0f * seek->mRunSpeed,
		0,
		seek->mShape->mHeading.z  * seek->mShape->mGame->mServer->mFrameTime / 1000.0f * seek->mRunSpeed,
		Node::TS_WORLD);
*/
}
void Normal_Seek::exit(Seek* seek)
{
}
bool Normal_Seek::onMessage(Seek* seek, const Telegram& msg)
{
        return true;
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
		seek->mStateMachine->changeState(Normal_Seek::Instance());
	}
}
void No_Seek::exit(Seek* seek)
{
}
bool No_Seek::onMessage(Seek* seek, const Telegram& msg)
{
        return true;
}

