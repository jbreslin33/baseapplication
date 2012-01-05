#include "shapeTagAll.h"

//log
#include "../tdreamsock/dreamSockLog.h"

//game
#include "../game/gameTagAll.h"

//math
#include "../../math/vector3D.h"

ShapeTagAll::ShapeTagAll(unsigned int index, GameTagAll* gameTagAll, Client* client, Vector3D* position, Vector3D* velocity, Vector3D* rotation, Ogre::Root* root,
			 bool animated ,bool collidable, float collisionRadius, int meshCode, bool ai)
	:
		ShapeTag(index, gameTagAll,client,position,velocity,rotation,root,animated,collidable,collisionRadius,meshCode,ai)

{
	mGameTagAll = gameTagAll;
}
	
ShapeTagAll::~ShapeTagAll()
{
}

int ShapeTagAll::setFlag()
{
	int flags = Shape::setFlag();
	
	if (mGameTag->mShapeIt == this)
	{
		flags |= mCommandIt;
	}
	
	return flags;
}




