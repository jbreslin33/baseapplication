#include "shapePartido.h"

//log
#include "../../tdreamsock/dreamSockLog.h"

//game
#include "../../network/network.h"

//game
#include "../../server/partido/serverPartido.h"

//game
#include "../../game/partido/gamePartido.h"

//client
#include "../../client/partido/clientPartido.h"

//math
#include "../../../math/vector3D.h"

//postgresql
#include <stdio.h>
#include <postgresql/libpq-fe.h>

ShapePartido::ShapePartido(unsigned int index, GamePartido* gamePartido, ClientPartido* clientPartido, Vector3D* position, Vector3D* velocity, Vector3D* rotation, Ogre::Root* root,
			 bool animated ,bool collidable, float collisionRadius, int meshCode, bool ai)
	:
		Shape(index, gamePartido,clientPartido,position,velocity,rotation,root,animated,collidable,collisionRadius,meshCode,ai)

{
	mGamePartido   = gamePartido;
	mClientPartido = clientPartido;
	mOpponent     = NULL;
	mOpponentLast = NULL;

        //register with shapePartido vector
        mGamePartido->mShapePartidoVector.push_back(this);

	//setText
	mClientPartido->setBattleRecordText();	
	setText(mClientPartido->mBattleRecordText);	
}
	
ShapePartido::~ShapePartido()
{
}

void ShapePartido::processTick()
{
	Shape::processTick();
}

void ShapePartido::collision(Shape* shape)
{
	Shape::collision(shape);	

	if (mOpponent == NULL && mOpponentLast != shape)
	{
		if (mClientPartido)
		{
			mClientPartido->battleStart((ShapePartido*)shape);
		}
	}
}
