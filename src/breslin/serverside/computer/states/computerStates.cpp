//parent
#include "computerStates.h"

//log
#include "../../tdreamsock/dreamSockLog.h"

//ability
#include "../computer.h"

//game
#include "../../game/game.h"

//shapes
#include "../../shape/shape.h"

//client
#include "../../client/robust/clientRobust.h"

//steering
#include "../../steering/steering.h"

//seek
#include "../../seek/seek.h"

//avoid
#include "../../avoid/avoid.h"

//move
#include "../../move/move.h"

//rotation
#include "../../rotation/rotation.h"

//vector3D
#include "../../../math/vector3D.h"

//rand
#include <stdlib.h>
#include <time.h>

#define MAX_RUN_SPEED 1.66           // character running speed in units per second


/*****************************************
*******       GLOBAL    ******************
****************************************/
GlobalComputer* GlobalComputer::Instance()
{
  static GlobalComputer instance;
  return &instance;
}
void GlobalComputer::enter(Computer* computer)
{
}
void GlobalComputer::execute(Computer* computer)
{

}
void GlobalComputer::exit(Computer* computer)
{
}
bool GlobalComputer::onLetter(Computer* computer, Letter* letter)
{
        return true;
}


/*****************************************
*******       COMPUTER    ******************
****************************************/

/*****************************************
*******      RANDOM COMPUTER    ******************
****************************************/
/*   Computer_Controlled   */
Computer_Controlled* Computer_Controlled::Instance()
{
  static Computer_Controlled instance;
  return &instance;
}

void Computer_Controlled::enter(Computer* computer)
{
    	if (computer->mShape->mAvoid)
        {
                if (computer->mShape->mClient->db_id == 5)
                {
                        for (int i = 0; i < computer->mShape->mGame->mShapeVector.size(); i++)
                        {
                                if (computer->mShape->mGame->mShapeVector.at(i)->mClient->db_id == 4)
                                {
                                        computer->mShape->mAvoid->addAvoidShape(computer->mShape->mGame->mShapeVector.at(i));
                                }

                                if (computer->mShape->mGame->mShapeVector.at(i)->mClient->db_id == 3)
                                {
                                        computer->mShape->mAvoid->addAvoidShape(computer->mShape->mGame->mShapeVector.at(i));
                                }
/*
                                if (computer->mShape->mGame->mShapeVector.at(i)->mClient->db_id == 2)
                                {
                                        computer->mShape->mAvoid->addAvoidShape(computer->mShape->mGame->mShapeVector.at(i));
                                }
*/
                        }
                }
        }

}

void Computer_Controlled::execute(Computer* computer)
{

       	if (computer->mShape->mSeek)
        {
                if (computer->mShape->mClient->db_id == 5)
                {
                        for (int i = 0; i < computer->mShape->mGame->mShapeVector.size(); i++)
                        {
                                if (computer->mShape->mGame->mShapeVector.at(i)->mClient->db_id == 2)
                                {
                                        computer->mShape->mSeek->setSeekShape(computer->mShape->mGame->mShapeVector.at(i));     
                                }
                        }
                }
        }

/*
	if (computer->mShape->mClient->db_id == 5)
	{
		Vector3D* target = new Vector3D(200.0f,0.0f,200.0f);
		computer->mShape->mSteering->setTarget(target);
		computer->mShape->mSteering->mSeekOn = true;
	}
*/	
	//is this human controlled?
	if (computer->mShape->mClient->mLoggedIn)
	{
		computer->mStateMachine->changeState(Human_Controlled::Instance());
	}
}

void Computer_Controlled::exit(Computer* computer)
{
}
bool Computer_Controlled::onLetter(Computer* computer, Letter* letter)
{
        return true;
}



/*****************************************
*******      RANDOM COMPUTER    ******************
****************************************/
Human_Controlled* Human_Controlled::Instance()
{
	static Human_Controlled instance;
	return &instance;
}

void Human_Controlled::enter(Computer* computer)
{
}

void Human_Controlled::execute(Computer* computer)
{
	if (!computer->mShape->mClient->mLoggedIn)
	{
		computer->mStateMachine->changeState(Computer_Controlled::Instance());
	}

 	computer->mShape->mMove->mVelocity->x = 0;
        computer->mShape->mMove->mVelocity->y = 0;
        computer->mShape->mMove->mVelocity->z = 0;

        // keep track of the player's intended direction
        if(computer->mShape->mClient->mKey & computer->mShape->mClient->mKeyUp)
        {
                computer->mShape->mMove->mVelocity->z += -1;
        }

        if(computer->mShape->mClient->mKey & computer->mShape->mClient->mKeyLeft)
        {
                computer->mShape->mMove->mVelocity->x += -1;
        }

        if(computer->mShape->mClient->mKey & computer->mShape->mClient->mKeyDown)
        {
                computer->mShape->mMove->mVelocity->z += 1;
        }
  
        if(computer->mShape->mClient->mKey & computer->mShape->mClient->mKeyRight)
        {
                computer->mShape->mMove->mVelocity->x += 1;
        }

        computer->mShape->mMove->mVelocity->normalise();

	//Rotation
        computer->mShape->mRotation->mDegrees = 0.0f;
        // keep track of the player's intended rotation
        if(computer->mShape->mClient->mKey & computer->mShape->mClient->mKeyCounterClockwise)
        {
                computer->mShape->mRotation->mDegrees += -1;
        }
        if(computer->mShape->mClient->mKey & computer->mShape->mClient->mKeyClockwise)
        {
                computer->mShape->mRotation->mDegrees += 1;
        }

}

void Human_Controlled::exit(Computer* computer)
{
}
bool Human_Controlled::onLetter(Computer* computer, Letter* letter)
{
        return true;
}

