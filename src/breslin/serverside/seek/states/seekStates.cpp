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
	//LogString("Normal");
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
		seek->mSeekVelocity->normalise();

		//set to shape velocity
		seek->mShape->mMove->mVelocity->copyValuesFrom(seek->mSeekVelocity);

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
bool No_Seek::onLetter(Seek* seek, Letter* letter)
{
        return true;
}

