#include "shapeTag.h"

ShapeTag::ShapeTag(Game* game, Client* client, Vector3D* position, Vector3D* velocity, Vector3D* rotation, Ogre::Root* root,
			 bool animated ,bool collidable, float collisionRadius, int meshCode, bool ai)
	:
		Shape(game,client,position,velocity,rotation,root,animated,collidable,collisionRadius,meshCode,ai)

{
	
}
	
ShapeTag::~ShapeTag()
{
}
