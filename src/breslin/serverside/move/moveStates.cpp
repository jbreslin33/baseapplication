#include "moveStates.h"
#include "../tdreamsock/dreamSockLog.h"

#include "moveStateMachine.h"

#include "move.h"

#include "../../command/command.h"

#define MAX_RUN_SPEED 1.66           // character running speed in units per second

Normal_Move* Normal_Move::Instance()
{
  static Normal_Move instance;
  return &instance;
}
void Normal_Move::enter(Move* move)
{

}
void Normal_Move::execute(Move* move)
{
	
	//check for No_move and Decelerate and Accelerate states..
    if (move->mKeyDirection.isZeroLength()) 
	{
		if(move->mRunSpeed > 0.0) //Decelerate_Move
		{
			move->mMoveStateMachine->changeState(Decelerate_Move::Instance());
			return;
		}
        else //No_Move
		{
			move->mMoveStateMachine->changeState(No_Move::Instance());
			return;
		}
    }
	else 
	{
        if(move->mRunSpeed < MAX_RUN_SPEED) //Accelerate_Move
		{
			move->mMoveStateMachine->changeState(Accelerate_Move::Instance());
			return;
		}
	}

	//actual move
	move->mSceneNode->translate(move->mKeyDirection.x * move->mCommand.mClientFrametime * move->mRunSpeed,
		0,
		move->mKeyDirection.z  * move->mCommand.mClientFrametime * move->mRunSpeed,
		Node::TS_WORLD);
}
void Normal_Move::exit(Move* move)
{
}

No_Move* No_Move::Instance()
{
	static No_Move instance;
	return &instance;
}
void No_Move::enter(Move* move)
{
}
void No_Move::execute(Move* move)
{
    if (move->mKeyDirection.isZeroLength()) 
	{
		if(move->mRunSpeed > 0.0) //Decelerate_Move
		{
			move->mMoveStateMachine->changeState(Decelerate_Move::Instance());
			return;
		}
        else //No_Move
		{
           move->mRunSpeed = 0.0;
		}
    }
	else 
	{
        if(move->mRunSpeed < MAX_RUN_SPEED) //Accelerate_Move
		{
			move->mMoveStateMachine->changeState(Accelerate_Move::Instance());
			return;
		}
		else //Normal_Move 
		{
			move->mMoveStateMachine->changeState(Normal_Move::Instance());
			return;
		}
	}
}
void No_Move::exit(Move* move)
{
}

Accelerate_Move* Accelerate_Move::Instance()
{
	static Accelerate_Move instance;
	return &instance;
}
void Accelerate_Move::enter(Move* move)
{
}
void Accelerate_Move::execute(Move* move)
{
    if (move->mKeyDirection.isZeroLength()) 
	{
		if(move->mRunSpeed > 0.0) //Decelerate_Move
		{
			move->mMoveStateMachine->changeState(Decelerate_Move::Instance());
			return;
		}
        else //No_Move
		{
			move->mMoveStateMachine->changeState(No_Move::Instance());
			return;
		}
    }
	else 
	{
        if(move->mRunSpeed < MAX_RUN_SPEED) //Accelerate_Move
		{
			move->mRunSpeed += move->mRunAccel;
		}
		else //Normal_Move 
		{
			move->mMoveStateMachine->changeState(Normal_Move::Instance());
			return;
		}
	}

	//actual move
	move->mSceneNode->translate(move->mKeyDirection.x * move->mCommand.mClientFrametime * move->mRunSpeed,
		0,
		move->mKeyDirection.z  * move->mCommand.mClientFrametime * move->mRunSpeed,
		Node::TS_WORLD);
}
void Accelerate_Move::exit(Move* move)
{
}

Decelerate_Move* Decelerate_Move::Instance()
{
	static Decelerate_Move instance;
	return &instance;
}
void Decelerate_Move::enter(Move* move)
{
}
void Decelerate_Move::execute(Move* move)
{
    if (move->mKeyDirection.isZeroLength()) 
	{
		if(move->mRunSpeed > 0.0) //Decelerate_Move
		{
			move->mRunSpeed -= move->mRunDecel;
		}
        else //No_Move
		{
			move->mMoveStateMachine->changeState(No_Move::Instance());
			return;
		}
    }
	else 
	{
        if(move->mRunSpeed < MAX_RUN_SPEED) //Accelerate_Move
		{
			move->mMoveStateMachine->changeState(Accelerate_Move::Instance());
			return;
		}
		else //Normal_Move 
		{
			move->mMoveStateMachine->changeState(Normal_Move::Instance());
			return;
		}
	}

	//actual move
	move->mSceneNode->translate(move->mKeyDirection.x * move->mCommand.mClientFrametime * move->mRunSpeed,
		0,
		move->mKeyDirection.z  * move->mCommand.mClientFrametime * move->mRunSpeed,
		Node::TS_WORLD);
}
void Decelerate_Move::exit(Move* move)
{
}
