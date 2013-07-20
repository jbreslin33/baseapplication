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
bool GlobalSeek::onLetter(Seek* seek, Letter* letter)
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
	LogString("Normal_Seek");
}
void Normal_Seek::execute(Seek* seek)
{
	if (seek->mSeekShape || seek->mSeekPoint)
        {
               	//current position 
		Vector3D* currentPosition = new Vector3D();
		currentPosition->convertFromVector3(seek->mShape->mSceneNode->getPosition());

		//seek velocity and length
                seek->mSeekVelocity->subtract(seek->mSeekPoint,currentPosition);
		seek->mSeekLength = seek->mSeekVelocity->length(); 			
		
		if (seek->mSeekLength <= 2) //close enough goto reachdestination
		{
                	seek->mStateMachine->changeState(Reached_Destination::Instance());
		}
		else //still not close enough seek on
		{
			seek->mSeekVelocity->normalise();

			//set to shape velocity
			seek->mShape->mMove->mVelocity->copyValuesFrom(seek->mSeekVelocity);
		}
        }
        else
        {
                seek->mStateMachine->changeState(No_Seek::Instance());
        }
}
void Normal_Seek::exit(Seek* seek)
{
}
bool Normal_Seek::onLetter(Seek* seek, Letter* letter)
{
        return true;
}

/*****************************************
        Reached_Destination
****************************************/
Reached_Destination* Reached_Destination::Instance()
{
        static Reached_Destination instance;
        return &instance;
}
void Reached_Destination::enter(Seek* seek)
{
        LogString("Reached_Destination");
}
void Reached_Destination::execute(Seek* seek)
{
        if (seek->mSeekShape == NULL && seek->mSeekPoint == NULL)
	{
                seek->mStateMachine->changeState(No_Seek::Instance());
	}
	else
	{
   		//current position
                Vector3D* currentPosition = new Vector3D();
                currentPosition->convertFromVector3(seek->mShape->mSceneNode->getPosition());

                //seek velocity and length
                seek->mSeekVelocity->subtract(seek->mSeekPoint,currentPosition);
                seek->mSeekLength = seek->mSeekVelocity->length();

		if (seek->mSeekLength > 2) //go to normal seek and seek on!
		{
                	seek->mStateMachine->changeState(Normal_Seek::Instance());
		}
		else
		{
                	//set to shape velocity to zero as you have reached destination
                	seek->mShape->mMove->mVelocity->zero();
		}
	}
}
void Reached_Destination::exit(Seek* seek)
{
}
bool Reached_Destination::onLetter(Seek* seek, Letter* letter)
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
	LogString("No_Seek");
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
bool No_Seek::onLetter(Seek* seek, Letter* letter)
{
        return true;
}

