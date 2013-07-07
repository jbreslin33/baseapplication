//parent
#include "aiStates.h"

//log
#include "../../../tdreamsock/dreamSockLog.h"

//states
#include "aiStateMachine.h"

//ability
#include "../ai.h"

//game
#include "../../../game/game.h"

//shapes
#include "../../../shape/shape.h"

//client
#include "../../../client/client.h"

//seek
#include "../../seek/seek.h"

//seek
#include "../../move/move.h"

//seek
#include "../../rotation/rotation.h"

//vector3D
#include "../../../../math/vector3D.h"

//rand
#include <stdlib.h>
#include <time.h>

#define MAX_RUN_SPEED 1.66           // character running speed in units per second

/*   Random_AI   */
Random_AI* Random_AI::Instance()
{
  static Random_AI instance;
  return &instance;
}

void Random_AI::enter(AI* ai)
{

}

void Random_AI::execute(AI* ai)
{
	if (ai->mShape->mSeek)
	{
		if (ai->mShape->mClient->db_id == 5)
		{
			/*
			Vector3D* seekPoint = new Vector3D(200.0f,0.0f,100.0f);
			ai->mShape->mSeek->setSeekPoint(seekPoint);
			*/
			for (int i = 0; i < ai->mShape->mGame->mShapeVector.size(); i++)
			{
				if (ai->mShape->mGame->mShapeVector.at(i)->mClient->db_id == 4)
				{
					ai->mShape->mSeek->setSeekShape(ai->mShape->mGame->mShapeVector.at(i));	
				}
			}
		}
	}

	//is this human controlled?
	if (ai->mShape->mClient->mConnectionState == 1)
	{
		ai->mAIStateMachine->changeState(Human_AI::Instance());
	}
}

void Random_AI::exit(AI* ai)
{
}

/*   Human_AI   */
Human_AI* Human_AI::Instance()
{
	static Human_AI instance;
	return &instance;
}

void Human_AI::enter(AI* ai)
{
}

void Human_AI::execute(AI* ai)
{
	if (ai->mShape->mClient->mConnectionState == 4)
	{
		ai->mAIStateMachine->changeState(Random_AI::Instance());
	}

 	ai->mShape->mMove->mHeading->x = 0;
        ai->mShape->mMove->mHeading->y = 0;
        ai->mShape->mMove->mHeading->z = 0;

        // keep track of the player's intended direction
        if(ai->mShape->mClient->mKey & ai->mShape->mClient->mKeyUp)
        {
                ai->mShape->mMove->mHeading->z += -1;
        }

        if(ai->mShape->mClient->mKey & ai->mShape->mClient->mKeyLeft)
        {
                ai->mShape->mMove->mHeading->x += -1;
        }

        if(ai->mShape->mClient->mKey & ai->mShape->mClient->mKeyDown)
        {
                ai->mShape->mMove->mHeading->z += 1;
        }
  
        if(ai->mShape->mClient->mKey & ai->mShape->mClient->mKeyRight)
        {
                ai->mShape->mMove->mHeading->x += 1;
        }

        ai->mShape->mMove->mHeading->normalise();

	//Rotation
        ai->mShape->mRotation->mDegrees = 0.0f;
        // keep track of the player's intended rotation
        if(ai->mShape->mClient->mKey & ai->mShape->mClient->mKeyCounterClockwise)
        {
                ai->mShape->mRotation->mDegrees += -1;
        }
        if(ai->mShape->mClient->mKey & ai->mShape->mClient->mKeyClockwise)
        {
                ai->mShape->mRotation->mDegrees += 1;
        }

}

void Human_AI::exit(AI* ai)
{
}

