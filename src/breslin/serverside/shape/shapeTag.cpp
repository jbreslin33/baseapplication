#include "shapeTag.h"

//math
#include "../../math/vector3D.h"

ShapeTag::ShapeTag(unsigned int index, Game* game, Client* client, Vector3D* position, Vector3D* velocity, Vector3D* rotation, Ogre::Root* root,
			 bool animated ,bool collidable, float collisionRadius, int meshCode, bool ai)
	:
		Shape(index, game,client,position,velocity,rotation,root,animated,collidable,collisionRadius,meshCode,ai)

{
	
}
	
ShapeTag::~ShapeTag()
{
}


void ShapeTag::buildDeltaMoveCommand(Message* mes)
{
	int flags = setFlag();
	buildDeltaMoveMessage(flags,mes);
}


int ShapeTag::setFlag()
{

	int flags = 0;

	//Origin
	if(mPosition->x != mPositionLast->x)
	{
		flags |= mCommandOriginX;
	}
	if(mPosition->y != mPositionLast->y)
	{
		flags |= mCommandOriginY;
	}
	if(mPosition->z != mPositionLast->z)
	{
		flags |= mCommandOriginZ;
	}

	//Rotation
	if(mRotation->x != mRotationLast->x)
	{
		flags |= mCommandRotationX;
	}
	if(mRotation->z != mRotationLast->z)
	{
		flags |= mCommandRotationZ;
	}
	
	//Milliseconds
	if(mMillisecondsTotal != mMillisecondsTotalLast)
	{
		flags |= mCommandMilliseconds;
	}

	return flags;
}

void ShapeTag::buildDeltaMoveMessage(int flags, Message* message)
{
	Shape::buildDeltaMoveMessage(flags,message);
}