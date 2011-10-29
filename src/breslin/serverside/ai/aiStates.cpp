//parent
#include "aiStates.h"

//log
#include "../tdreamsock/dreamSockLog.h"

//states
#include "aiStateMachine.h"

//ability
#include "ai.h"

//game
#include "../game/game.h"

//shapes
#include "../shape/shape.h"

//commands
#include "../command/command.h"

//rand
#include <stdlib.h>
#include <time.h>

#define MAX_RUN_SPEED 1.66           // character running speed in units per second

Normal_AI* Normal_AI::Instance()
{
  static Normal_AI instance;
  return &instance;
}
void Normal_AI::enter(AI* ai)
{
}
void Normal_AI::execute(AI* ai)
{
}
void Normal_AI::exit(AI* ai)
{
}


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

	srand ( (short)time(NULL) + ai->mShape->mIndex);	/* initialize random seed: */
	ai->mShape->mCommand.mKey = rand() % 16 + 1;  //assign random key 0-16 or is it 1-16 or 0-15?

	if (ai->mShape->mCommand.mKey == 16)
	{
		ai->mShape->mCommand.mKey = 2;
	}
	if (ai->mShape->mCommand.mKey == 0)
	{
		ai->mShape->mCommand.mKey = 4;
	}

	//let's set them both because right now brian uses both. but for us ai guys they should be the same number???
	ai->mShape->mCommand.mMillisecondsTotal = ai->mShape->mGame->mFrameTime;
	ai->mShape->mCommand.mMilliseconds = ai->mShape->mGame->mFrameTime;

	ai->mShape->mCommand.mClientFrametime = ai->mShape->mCommand.mMillisecondsTotal / 1000.0f;

}
void Random_AI::exit(AI* ai)
{
}

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
}
void No_AI::exit(AI* ai)
{
}

Accelerate_AI* Accelerate_AI::Instance()
{
	static Accelerate_AI instance;
	return &instance;
}
void Accelerate_AI::enter(AI* ai)
{
}
void Accelerate_AI::execute(AI* ai)
{
}
void Accelerate_AI::exit(AI* ai)
{
}

Decelerate_AI* Decelerate_AI::Instance()
{
	static Decelerate_AI instance;
	return &instance;
}
void Decelerate_AI::enter(AI* ai)
{
}
void Decelerate_AI::execute(AI* ai)
{
}
void Decelerate_AI::exit(AI* ai)
{
}
