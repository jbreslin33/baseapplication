#include "shapeTagPlayer.h"

ShapeTagPlayer::ShapeTagPlayer(Client* client, Vector3D* position, Vector3D* velocity, Vector3D* rotation, Ogre::Root* root,unsigned int index,
			 bool animated ,bool collidable, float collisionRadius, int meshCode, bool ai)
	:
		ShapeTag(client,position,velocity,rotation,root,index,animated,collidable,collisionRadius,meshCode,ai)

{
	
}
	
ShapeTagPlayer::~ShapeTagPlayer()
{
}
