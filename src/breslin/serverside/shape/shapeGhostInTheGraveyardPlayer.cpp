#include "shapeGhostInTheGraveyardPlayer.h"

ShapeGhostInTheGraveyardPlayer::ShapeGhostInTheGraveyardPlayer(Vector3D* position, Vector3D* velocity, Vector3D* rotation, Ogre::Root* root,unsigned int index,
			 bool animated ,bool collidable, float collisionRadius, int meshCode, bool ai)
	:
		Shape(position,velocity,rotation,root,index,animated,collidable,collisionRadius,meshCode,ai)

{
	
}
	
ShapeGhostInTheGraveyardPlayer::~ShapeGhostInTheGraveyardPlayer()
{
}
