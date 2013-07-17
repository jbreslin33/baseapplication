//parent
#include "moveStates.h"

//log
#include "../../tdreamsock/dreamSockLog.h"

//ability
#include "../move.h"

//server
#include "../../server/server.h"

//game
#include "../../game/game.h"

//shape
#include "../../shape/shape.h"

//vector3d
#include "../../../math/vector3D.h"

//client
#include "../../client/robust/clientRobust.h"

/*****************************************
*******       GLOBAL    ******************
****************************************/
GlobalMove* GlobalMove::Instance()
{
  static GlobalMove instance;
  return &instance;
}
void GlobalMove::enter(Move* move)
{
}
void GlobalMove::execute(Move* move)
{
}
void GlobalMove::exit(Move* move)
{
}
bool GlobalMove::onLetter(Move* move, Letter* letter)
{
        return true;
}


/*****************************************
	Normal_Move
****************************************/
Normal_Move* Normal_Move::Instance()
{
  static Normal_Move instance;
  return &instance;
}
void Normal_Move::enter(Move* move)
{
	//LogString("Normal");
}
void Normal_Move::execute(Move* move)
{
	if (move->mShape->mClient->db_id == 5)
	{
		LogString("Normal_Move");
		LogString("xm:%f",move->mVelocity->x);	
		LogString("zm:%f",move->mVelocity->z);	
	}
	//check for No_move and Decelerate and Accelerate states..
    	if (move->mVelocity->isZero()) 
	{
		if(move->mRunSpeed > 0.0) //Decelerate_Move
		{
			move->mStateMachine->changeState(Decelerate_Move::Instance());
			return;
		}
        	else //No_Move
		{
			move->mStateMachine->changeState(No_Move::Instance());
			return;
		}
    	}
	else 
	{
        	if(move->mRunSpeed < move->mSpeedMax) //Accelerate_Move
		{
			move->mStateMachine->changeState(Accelerate_Move::Instance());
			return;
		}
	}


	//actual move
	move->mShape->mSceneNode->translate(move->mVelocity->x * move->mShape->mGame->mServer->mFrameTime / 1000.0f * move->mRunSpeed,
		0,
		move->mVelocity->z  * move->mShape->mGame->mServer->mFrameTime / 1000.0f * move->mRunSpeed,
		Node::TS_WORLD);
}
void Normal_Move::exit(Move* move)
{
}
bool Normal_Move::onLetter(Move* move, Letter* letter)
{
        return true;
}

/*****************************************
	No_Move
****************************************/
No_Move* No_Move::Instance()
{
	static No_Move instance;
	return &instance;
}
void No_Move::enter(Move* move)
{
	//LogString("No");
}
void No_Move::execute(Move* move)
{
	if (move->mShape->mClient->db_id == 5)
	{
		LogString("No_Move");
		LogString("xm:%f",move->mVelocity->x);	
		LogString("zm:%f",move->mVelocity->z);	
	}
	if (move->mVelocity->isZero()) 
	{
		if(move->mRunSpeed > 0.0) //Decelerate_Move
		{
			move->mStateMachine->changeState(Decelerate_Move::Instance());
			return;
		}
        	else //No_Move
		{
           		move->mRunSpeed = 0.0;
		}
    	}
	else 
	{
        	if(move->mRunSpeed < move->mSpeedMax) //Accelerate_Move
		{
			move->mStateMachine->changeState(Accelerate_Move::Instance());
			return;
		}
		else //Normal_Move 
		{
			move->mStateMachine->changeState(Normal_Move::Instance());
			return;
		}
	}
}
void No_Move::exit(Move* move)
{
}
bool No_Move::onLetter(Move* move, Letter* letter)
{
        return true;
}

/*****************************************
	Accelerate_Move
****************************************/
Accelerate_Move* Accelerate_Move::Instance()
{
	static Accelerate_Move instance;
	return &instance;
}
void Accelerate_Move::enter(Move* move)
{
	//LogString("Accelerate");
}
void Accelerate_Move::execute(Move* move)
{
	if (move->mShape->mClient->db_id == 5)
	{
		LogString("Accelerate");
		LogString("xm:%f",move->mVelocity->x);	
		LogString("zm:%f",move->mVelocity->z);	
	}
	if (move->mVelocity->isZero()) 
	{
		if(move->mRunSpeed > 0.0) //Decelerate_Move
		{
			move->mStateMachine->changeState(Decelerate_Move::Instance());
			return;
		}
        	else //No_Move
		{
			move->mStateMachine->changeState(No_Move::Instance());
			return;
		}
    	}
	else 
	{
        	if(move->mRunSpeed < move->mSpeedMax) //Accelerate_Move
		{
			move->mRunSpeed += move->mRunAccel;
		}
		else //Normal_Move 
		{
			move->mStateMachine->changeState(Normal_Move::Instance());
			return;
		}
	}

	//actual move
	move->mShape->mSceneNode->translate(move->mVelocity->x * move->mShape->mGame->mServer->mFrameTime / 1000.0f * move->mRunSpeed,
		0,
		move->mVelocity->z  * move->mShape->mGame->mServer->mFrameTime / 1000.0f * move->mRunSpeed,
		Node::TS_WORLD);
}
void Accelerate_Move::exit(Move* move)
{
}
bool Accelerate_Move::onLetter(Move* move, Letter* letter)
{
        return true;
}

/*****************************************
	Decelerate_Move
****************************************/
Decelerate_Move* Decelerate_Move::Instance()
{
	static Decelerate_Move instance;
	return &instance;
}
void Decelerate_Move::enter(Move* move)
{
	//LogString("Decelerate");
}
void Decelerate_Move::execute(Move* move)
{
	if (move->mShape->mClient->db_id == 5)
	{
		LogString("Decelerate");
		LogString("xm:%f",move->mVelocity->x);	
		LogString("zm:%f",move->mVelocity->z);	
	}
    	if (move->mVelocity->isZero()) 
	{
		if(move->mRunSpeed > 0.0) //Decelerate_Move
		{
			move->mRunSpeed -= move->mRunDecel;
		}
        	else //No_Move
		{
			move->mStateMachine->changeState(No_Move::Instance());
			return;
		}
    	}
	else 
	{
        	if(move->mRunSpeed < move->mSpeedMax) //Accelerate_Move
		{
			move->mStateMachine->changeState(Accelerate_Move::Instance());
			return;
		}
		else //Normal_Move 
		{
			move->mStateMachine->changeState(Normal_Move::Instance());
			return;
		}
	}

	//actual move
	move->mShape->mSceneNode->translate(move->mVelocity->x * move->mShape->mGame->mServer->mFrameTime / 1000.0f * move->mRunSpeed,
		0,
		move->mVelocity->z  * move->mShape->mGame->mServer->mFrameTime / 1000.0f * move->mRunSpeed,
		Node::TS_WORLD);
}
void Decelerate_Move::exit(Move* move)
{
}
bool Decelerate_Move::onLetter(Move* move, Letter* letter)
{
        return true;
}
