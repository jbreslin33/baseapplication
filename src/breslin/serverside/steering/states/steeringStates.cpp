//parent
#include "steeringStates.h"

//log
#include "../../tdreamsock/dreamSockLog.h"

//steering
#include "../steering.h"

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
GlobalSteering* GlobalSteering::Instance()
{
  static GlobalSteering instance;
  return &instance;
}
void GlobalSteering::enter(Steering* steering)
{
}
void GlobalSteering::execute(Steering* steering)
{

}
void GlobalSteering::exit(Steering* steering)
{
}
bool GlobalSteering::onLetter(Steering* steering, Letter* letter)
{
        return true;
}


/*****************************************
	Normal_Steering
****************************************/
Normal_Steering* Normal_Steering::Instance()
{
  static Normal_Steering instance;
  return &instance;
}
void Normal_Steering::enter(Steering* steering)
{
	//LogString("Normal");
}
void Normal_Steering::execute(Steering* steering)
{
	if (steering->mSteeringShape || steering->mSteeringPoint)
	{
 		Vector3D* newKeyDirection = new Vector3D();
                Vector3D* currentPosition  = new Vector3D();

                currentPosition->x = steering->mShape->mSceneNode->getPosition().x;
                currentPosition->y = steering->mShape->mSceneNode->getPosition().y;
                currentPosition->z = steering->mShape->mSceneNode->getPosition().z;

                newKeyDirection->subtract(steering->mSteeringPoint,currentPosition);
                steering->mShape->mMove->mHeading->x = newKeyDirection->x;
               	steering->mShape->mMove->mHeading->y = newKeyDirection->y;
                steering->mShape->mMove->mHeading->z  = newKeyDirection->z;

                steering->mShape->mMove->mHeading->normalise();
	}
	else
	{
		steering->mStateMachine->changeState(No_Steering::Instance());
	}
}
void Normal_Steering::exit(Steering* steering)
{
}
bool Normal_Steering::onLetter(Steering* steering, Letter* letter)
{
        return true;
}

/*****************************************
	No_Steering
****************************************/
No_Steering* No_Steering::Instance()
{
	static No_Steering instance;
	return &instance;
}
void No_Steering::enter(Steering* steering)
{
	//LogString("No");
}
void No_Steering::execute(Steering* steering)
{
	if (steering->mSteeringShape == NULL && steering->mSteeringPoint == NULL)
	{
		//LogString("Not steeringing");
	}
	else
	{
		steering->mStateMachine->changeState(Normal_Steering::Instance());
	}
}
void No_Steering::exit(Steering* steering)
{
}
bool No_Steering::onLetter(Steering* steering, Letter* letter)
{
        return true;
}

