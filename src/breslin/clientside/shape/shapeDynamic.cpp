#include "shapeDynamic.h"
#include "../tdreamsock/dreamSockLog.h"

//game
#include "../game/game.h"

#include "../states/stateMachineShapeDynamic.h"
#include "../ability/move/abilityMoveStates.h"
#include "../ability/rotation/abilityRotationStates.h"


#include "../dispatch/dispatch.h"

#include "../billboard/objectTitle.h"

//ability
#include "../ability/rotation/abilityRotation.h"
#include "../ability/move/abilityMove.h"
#include "../ability/animation/abilityAnimation.h"


#include <string.h>

ShapeDynamic::ShapeDynamic(Game* game, Dispatch* dispatch)
:
	Shape         ()
{
	mGame = game;

	mPosition = new Vector3D();
	mVelocity = new Vector3D();
	mRotation = new Vector3D();

	parseDispatch(dispatch);
	initializeVariables();
	initializeCommands(mPosition,mRotation);
	createStateMachines();

	//ability
	mAbilityRotation = new AbilityRotation(this);
	mAbilityMove     = new AbilityMove(this);
	mAbilityAnimation = NULL;	
	
}

ShapeDynamic::~ShapeDynamic()
{

}

void ShapeDynamic::parseDispatch(Dispatch* dispatch)
{
	dispatch->BeginReading();
	dispatch->ReadByte(); //should read -103 to add a shape..
	mLocal	=    dispatch->ReadByte();
	mIndex		=    dispatch->ReadByte();
	dispatch->ReadString(); //strcpy(name, dispatch->ReadString()); //name
	mPosition->x =   dispatch->ReadFloat();
	mPosition->y =   dispatch->ReadFloat();
	mPosition->z =   dispatch->ReadFloat();
	mVelocity->x = dispatch->ReadFloat();
	mVelocity->y = dispatch->ReadFloat();
	mVelocity->z = dispatch->ReadFloat();
	mRotation->x = dispatch->ReadFloat();
	mRotation->z = dispatch->ReadFloat();
}

void ShapeDynamic::initializeVariables()
{
	//dynamic
	mRenderTime = 0.0;

	mGhost = NULL;
}

void ShapeDynamic::initializeCommands(Vector3D* position, Vector3D* rotation)
{
	//let's set the serverframe...for inititialize purposeses
	mServerFrame.mOrigin.x = position->x;
	mServerFrame.mOrigin.y = position->y;
	mServerFrame.mOrigin.z = position->z;

	mServerFrame.mOriginOld.x = position->x;
	mServerFrame.mOriginOld.y = position->y;
	mServerFrame.mOriginOld.z = position->z;

	mServerFrame.mVelocity.x = position->x;
	mServerFrame.mVelocity.y = position->y;
	mServerFrame.mVelocity.z = position->z;

	mServerFrame.mRot.x = rotation->x;
	mServerFrame.mRot.y = 0;
	mServerFrame.mRot.z = rotation->z;

	mServerFrame.mMilliseconds = 0;
	mServerFrame.mMillisecondsTotal = 0;

	mServerFrame.mKey = 0;
	mServerFrame.mRotSpeed = 0;

	//let's set the serverframe...for inititialize purposeses
	mCommandToRunOnShape.mOrigin.x = position->x;
	mCommandToRunOnShape.mOrigin.y = position->y;
	mCommandToRunOnShape.mOrigin.z = position->z;

	mCommandToRunOnShape.mOriginOld.x = position->x;
	mCommandToRunOnShape.mOriginOld.y = position->y;
	mCommandToRunOnShape.mOriginOld.z = position->z;

	mCommandToRunOnShape.mVelocity.x = position->x;
	mCommandToRunOnShape.mVelocity.y = position->y;
	mCommandToRunOnShape.mVelocity.z = position->z;

	mCommandToRunOnShape.mRot.x = rotation->x;
	mCommandToRunOnShape.mRot.y = 0;
	mCommandToRunOnShape.mRot.z = rotation->z;

	mCommandToRunOnShape.mMilliseconds = 0;
	mCommandToRunOnShape.mMillisecondsTotal = 0;

	mCommandToRunOnShape.mKey = 0;
	mCommandToRunOnShape.mRotSpeed = 0;

}

void ShapeDynamic::createStateMachines()
{
}

void ShapeDynamic::processTick()
{
	clearTitle(); //empty title string so it can be filled anew

	//update state machines...
	mAbilityRotation->processTick();
	mAbilityMove->processTick();

	//run billboard here for now.
	//drawTitle();
}
void ShapeDynamic::interpolateTick(float renderTime)
{
	mRenderTime = renderTime;

	//update state machines...
	mAbilityRotation->interpolateTick(mRenderTime);
	mAbilityMove->interpolateTick(mRenderTime);
	mAbilityAnimation->interpolateTick(mRenderTime);

}

//this is all shapes coming to client game from server
//should a shape be responsible to read it's own command?????
//once we determine it's about him shouldn't we pass it off to
//shape object to handle?
void ShapeDynamic::readDeltaMoveCommand(Dispatch *mes)
{
	//ShapeDynamic* shape = NULL;

	int flags = 0;

	bool x = true;
	bool z = true;
	bool y = true;

	// Flags
	flags = mes->ReadByte();

	// Origin
	if(flags & mCommandOriginX)
	{
		mServerFrame.mOriginOld.x = mServerFrame.mOrigin.x;
		mServerFrame.mOrigin.x = mes->ReadFloat();		
	}
	else
	{
		x = false;
	}

	if(flags & mCommandOriginY)
	{
		mServerFrame.mOriginOld.y = mServerFrame.mOrigin.y;
		mServerFrame.mOrigin.y = mes->ReadFloat();
	}
	else
	{
		y = false;
	}

	if(flags & mCommandOriginZ)
	{
		mServerFrame.mOriginOld.z = mServerFrame.mOrigin.z;
		mServerFrame.mOrigin.z = mes->ReadFloat();	
	}
	else
	{
		z = false;
	}

	//set old rot
	mServerFrame.mRotOld.x = mServerFrame.mRot.x;
	mServerFrame.mRotOld.z = mServerFrame.mRot.z;

	//rotation
	if(flags & mCommandRotationX)
	{
		mServerFrame.mRot.x = mes->ReadFloat();
	}

	if(flags & mCommandRotationZ)
	{
		mServerFrame.mRot.z = mes->ReadFloat();
	}

	//milliseconds
	if (flags & mCommandMilliseconds)
	{
		mServerFrame.mMilliseconds = mes->ReadByte();
		mCommandToRunOnShape.mMilliseconds = mServerFrame.mMilliseconds;
	}

	if (mServerFrame.mMilliseconds != 0) 
	{
		if(!x && !z && !y && mServerFrame.mMilliseconds != 0)
		{
			mServerFrame.mVelocity.x = 0.0;
			mServerFrame.mVelocity.y = 0.0;
			mServerFrame.mVelocity.z = 0.0;
		}
		else
		{
			mServerFrame.mVelocity.x = mServerFrame.mOrigin.x - mServerFrame.mOriginOld.x;
			mServerFrame.mVelocity.y = mServerFrame.mOrigin.y - mServerFrame.mOriginOld.y;
			mServerFrame.mVelocity.z = mServerFrame.mOrigin.z - mServerFrame.mOriginOld.z;
		}
	}
	processTick();
	moveGhostShape();
}


void ShapeDynamic::moveGhostShape()
{
	Vector3D transVector;

	transVector.x = mServerFrame.mOrigin.x;
	transVector.y = 0;
	transVector.z = mServerFrame.mOrigin.z;

	if (mGhost)
	{
		mGhost->setPosition(transVector);
	}
}
