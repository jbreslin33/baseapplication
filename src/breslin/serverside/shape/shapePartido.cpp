#include "shapePartido.h"

//log
#include "../tdreamsock/dreamSockLog.h"

//game
#include "../game/gamePartido.h"

//client
#include "../client/clientPartido.h"

//math
#include "../../math/vector3D.h"

ShapePartido::ShapePartido(unsigned int index, GamePartido* gamePartido, ClientPartido* clientPartido, Vector3D* position, Vector3D* velocity, Vector3D* rotation, Ogre::Root* root,
			 bool animated ,bool collidable, float collisionRadius, int meshCode, bool ai)
	:
		Shape(index, gamePartido,clientPartido,position,velocity,rotation,root,animated,collidable,collisionRadius,meshCode,ai)

{
	mGamePartido = gamePartido;
	mClientPartido = clientPartido;
	mInBattle = false;
}
	
ShapePartido::~ShapePartido()
{
}

void ShapePartido::processTick()
{
	if (mInBattle)
	{
		LogString("in Battle");
	}	
	else
	{
		Shape::processTick();
	}
}

