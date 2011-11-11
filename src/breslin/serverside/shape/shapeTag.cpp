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


void ShapeTag::addToMoveMessage(Message* message)
{
	Shape::addToMoveMessage(message);
	/*
	int flags = setFlag();

	message->WriteByte(mIndex);

	// Flags
	message->WriteByte(flags);  

	//Origin
	if(flags & mCommandOriginX)
	{
		message->WriteFloat(mPosition->x);
	}
	if(flags & mCommandOriginY)
	{
		message->WriteFloat(mPosition->y);
	}
	if(flags & mCommandOriginZ)
	{
		message->WriteFloat(mPosition->z);
	}

	//Rotation
	if(flags & mCommandRotationX)
	{
		message->WriteFloat(mRotation->x);
	}
	if(flags & mCommandRotationZ)
	{
		message->WriteFloat(mRotation->z);
	}

	//Milliseconds
	if(flags & mCommandMilliseconds)
	{
		message->WriteByte(mMillisecondsTotal);
	}
	*/
}




