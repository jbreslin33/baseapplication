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

        //register with shapePartido vector
        mGamePartido->mShapePartidoVector.push_back(this);
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

void ShapePartido::collision(Shape* shape)
{
	Shape::collision(shape);	
}

/*
void GamePartido::collision(Shape* shape1, Shape* shape2)
{
        Game::collision(shape1,shape2);

        //now let's check if these guys are already in a battle
        for (unsigned int i = 0; i < mBattleVector.size(); i++)
        {
                for (unsigned int s = 0; s < mBattleVector.at(i)->mShapePartidoVector.size(); s++)
                {
                        if (shape1 == mBattleVector.at(i)->mShapePartidoVector.at(s) || shape2 == mBattleVector.at(i)->mShapePartidoVector.at(s))
                        {
                                return;
                        }
                }
        }

        battleCollision((ShapePartido*)shape1,(ShapePartido*)shape2);
}

void GamePartido::battleCollision(ShapePartido* shapePartido1, ShapePartido* shapePartido2)
{
        std::vector<ShapePartido*> shapePartidoVector;
        shapePartidoVector.push_back(shapePartido1);
        shapePartidoVector.push_back(shapePartido2);

        //create a battle
        Battle* battle = new Battle(this,shapePartidoVector);
        mBattleVector.push_back(battle);
}
*/

