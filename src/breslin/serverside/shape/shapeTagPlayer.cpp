#include "shapeTagPlayer.h"

ShapeTagPlayer::ShapeTagPlayer(unsigned int index, Game* game, Client* client, Vector3D* position, Vector3D* velocity, Vector3D* rotation, Ogre::Root* root,
			 bool animated ,bool collidable, float collisionRadius, int meshCode, bool ai)
	:
		ShapeTag(index, game, client,position,velocity,rotation,root,animated,collidable,collisionRadius,meshCode,ai)

{
	mIt = false;
}
	
ShapeTagPlayer::~ShapeTagPlayer()
{

}
