//parent
#include "avoidStates.h"

//log
#include "../../tdreamsock/dreamSockLog.h"

//avoid
#include "../avoid.h"

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
GlobalAvoid* GlobalAvoid::Instance()
{
  static GlobalAvoid instance;
  return &instance;
}
void GlobalAvoid::enter(Avoid* avoid)
{
}
void GlobalAvoid::execute(Avoid* avoid)
{

}
void GlobalAvoid::exit(Avoid* avoid)
{
}
bool GlobalAvoid::onLetter(Avoid* avoid, Letter* letter)
{
        return true;
}


/*****************************************
	Normal_Avoid
****************************************/
Normal_Avoid* Normal_Avoid::Instance()
{
  static Normal_Avoid instance;
  return &instance;
}
void Normal_Avoid::enter(Avoid* avoid)
{
	//LogString("Normal");
}
void Normal_Avoid::execute(Avoid* avoid)
{
	
/*
	if (avoid->mAvoidShape || avoid->mAvoidPoint)
        {
                Vector3D* newKeyDirection = new Vector3D();
                Vector3D* currentPosition  = new Vector3D();

                currentPosition->x = avoid->mShape->mSceneNode->getPosition().x;
                currentPosition->y = avoid->mShape->mSceneNode->getPosition().y;
                currentPosition->z = avoid->mShape->mSceneNode->getPosition().z;

                newKeyDirection->subtract(avoid->mAvoidPoint,currentPosition);
                avoid->mShape->mMove->mVelocity->x = newKeyDirection->x;
                avoid->mShape->mMove->mVelocity->y = newKeyDirection->y;
                avoid->mShape->mMove->mVelocity->z = newKeyDirection->z;

                avoid->mShape->mMove->mVelocity->normalise();
        }
        else
        {
                avoid->mStateMachine->changeState(No_Avoid::Instance());
        }
*/
}
void Normal_Avoid::exit(Avoid* avoid)
{
}
bool Normal_Avoid::onLetter(Avoid* avoid, Letter* letter)
{
        return true;
}

/*****************************************
	No_Avoid
****************************************/
No_Avoid* No_Avoid::Instance()
{
	static No_Avoid instance;
	return &instance;
}
void No_Avoid::enter(Avoid* avoid)
{
	//LogString("No");
}
void No_Avoid::execute(Avoid* avoid)
{
	if (avoid->mAvoidShape == NULL && avoid->mAvoidPoint == NULL)
	{
		//LogString("Not avoiding");
	}
	else
	{
		avoid->mStateMachine->changeState(Normal_Avoid::Instance());
	}
}
void No_Avoid::exit(Avoid* avoid)
{
}
bool No_Avoid::onLetter(Avoid* avoid, Letter* letter)
{
        return true;
}

