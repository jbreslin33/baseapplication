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
	Seek* seek = (Seek*)ai->mShape->getAbility(seek);
	
	if (seek)
	{
		seek->mSeekPoint = new Vector3D(100.0f,0.0f,100.0f);	
	}

/*
	//is this human controlled?
	if (ai->mShape->mClient->mConnectionState == 1)
	{
		ai->mAIStateMachine->changeState(No_AI::Instance());
	}

	//have we reached threshold if so give a new mKey for random movement 
	if (ai->mCounter > ai->mThreshold)
	{
		ai->mShape->mKey = rand() % 32 + 1;  //assign random key 0-16 or is it 1-16 or 0-15?
		ai->mCounter = 0;
	}
	ai->mCounter++;
*/
}

void Random_AI::exit(AI* ai)
{
}

/*   No_AI   */
No_AI* No_AI::Instance()
{
	static No_AI instance;
	return &instance;
}

void No_AI::enter(AI* ai)
{
}

void No_AI::execute(AI* ai)
{
	if (ai->mShape->mClient->mConnectionState == 4)
	{
		ai->mAIStateMachine->changeState(Random_AI::Instance());
	}
}

void No_AI::exit(AI* ai)
{
}

