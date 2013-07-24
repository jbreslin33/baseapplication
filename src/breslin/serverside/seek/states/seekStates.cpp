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

//client
#include "../../client/robust/clientRobust.h"

/*****************************************
*******       GLOBAL    ******************
****************************************/
GLOBAL_SEEK* GLOBAL_SEEK::Instance()
{
  static GLOBAL_SEEK instance;
  return &instance;
}
void GLOBAL_SEEK::enter(Seek* seek)
{
}
void GLOBAL_SEEK::execute(Seek* seek)
{
	if (seek->mSeekPoint)
	{
		if (seek->mStateMachine->currentState() != NORMAL_SEEK::Instance())
		{
			seek->mStateMachine->changeState(NORMAL_SEEK::Instance());
		}
	}
	if (seek->mDestinationPoint)
	{
		if (seek->mStateMachine->currentState() != SEEK_DESTINATION::Instance())
		{ 
			seek->mStateMachine->changeState(SEEK_DESTINATION::Instance());
		}
	}
}
void GLOBAL_SEEK::exit(Seek* seek)
{
}
bool GLOBAL_SEEK::onLetter(Seek* seek, Letter* letter)
{
        return true;
}

/*****************************************
	NORMAL_SEEK
****************************************/
NORMAL_SEEK* NORMAL_SEEK::Instance()
{
  static NORMAL_SEEK instance;
  return &instance;
}
void NORMAL_SEEK::enter(Seek* seek)
{
	LogString("NORMAL_SEEK:%d",seek->mShape->mClient->db_id);
}
void NORMAL_SEEK::execute(Seek* seek)
{
	if (seek->mSeekShape || seek->mSeekPoint)
        {
               	//current position 
		Vector3D* currentPosition = new Vector3D();
		currentPosition->convertFromVector3(seek->mShape->mSceneNode->getPosition());

		//seek velocity and length
                seek->mSeekVelocity->subtract(seek->mSeekPoint,currentPosition);
		seek->mSeekLength = seek->mSeekVelocity->length(); 			
		
		seek->mSeekVelocity->normalise();

		//set to shape velocity
		seek->mShape->mMove->mVelocity->copyValuesFrom(seek->mSeekVelocity);
        }
        else
        {
                seek->mStateMachine->changeState(NO_SEEK::Instance());
        }
}
void NORMAL_SEEK::exit(Seek* seek)
{
}
bool NORMAL_SEEK::onLetter(Seek* seek, Letter* letter)
{
        return true;
}

/*****************************************
        SEEK_DESTINATION
****************************************/
SEEK_DESTINATION* SEEK_DESTINATION::Instance()
{
        static SEEK_DESTINATION instance;
        return &instance;
}
void SEEK_DESTINATION::enter(Seek* seek)
{
        LogString("SEEK_DESTINATION:%d",seek->mShape->mClient->db_id);
}
void SEEK_DESTINATION::execute(Seek* seek)
{
 	if (seek->mDestinationShape || seek->mDestinationPoint)
        {
                //current position
                Vector3D* currentPosition = new Vector3D();
                currentPosition->convertFromVector3(seek->mShape->mSceneNode->getPosition());

                //destination velocity and length
                seek->mDestinationVelocity->subtract(seek->mDestinationPoint,currentPosition);
                seek->mDestinationLength = seek->mDestinationVelocity->length();

                if (seek->mDestinationLength <= 1) //close enough goto reachdestination
                {
                        seek->mStateMachine->changeState(REACHED_DESTINATION::Instance());
                }
                else //still not close enough seek on
                {
                        seek->mDestinationVelocity->normalise();

                        //set to shape velocity
                        seek->mShape->mMove->mVelocity->copyValuesFrom(seek->mDestinationVelocity);
                }
        }
        else
        {
                seek->mStateMachine->changeState(NO_SEEK::Instance());
        }

}
void SEEK_DESTINATION::exit(Seek* seek)
{
}
bool SEEK_DESTINATION::onLetter(Seek* seek, Letter* letter)
{
        return true;
}

/*****************************************
        REACHED_DESTINATION
****************************************/
REACHED_DESTINATION* REACHED_DESTINATION::Instance()
{
        static REACHED_DESTINATION instance;
        return &instance;
}
void REACHED_DESTINATION::enter(Seek* seek)
{
        LogString("REACHED_DESTINATION:%d",seek->mShape->mClient->db_id);
        //set to shape velocity to zero as you have reached destination
        seek->mShape->mMove->mVelocity->zero();
	seek->setDestinationShape(NULL);
}
void REACHED_DESTINATION::execute(Seek* seek)
{
}
void REACHED_DESTINATION::exit(Seek* seek)
{
}
bool REACHED_DESTINATION::onLetter(Seek* seek, Letter* letter)
{
        return true;
}



/*****************************************
	NO_SEEK
****************************************/
NO_SEEK* NO_SEEK::Instance()
{
	static NO_SEEK instance;
	return &instance;
}
void NO_SEEK::enter(Seek* seek)
{
	LogString("NO_SEEK:%d",seek->mShape->mClient->db_id);
}
void NO_SEEK::execute(Seek* seek)
{
}
void NO_SEEK::exit(Seek* seek)
{
}
bool NO_SEEK::onLetter(Seek* seek, Letter* letter)
{
        return true;
}

