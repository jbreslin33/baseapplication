//parent
#include "shapePartidoStates.h"

//log
#include "../../../tdreamsock/dreamSockLog.h"

//states
#include "../../../../fsm/stateMachine.h"

//ability
#include "../shapePartido.h"

//server
#include "../../../server/server.h"

//client
#include "../../../client/robust/partido/clientPartido.h"

//clientPartido states
#include "../../../client/robust/partido/states/clientPartidoStates.h"

//move
#include "../../../move/move.h"

//vector3D
#include "../../../../math/vector3D.h"

//test
#include "../../../test/test.h"

//battle
#include "../../../battle/battle.h"

//combatant
#include "../../../combatant/combatant.h"

//game
#include "../../../game/partido/gamePartido.h"


/*****************************************
*******       GLOBAL    ******************
****************************************/
GLOBAL_SHAPE_PARTIDO* GLOBAL_SHAPE_PARTIDO::Instance()
{
  static GLOBAL_SHAPE_PARTIDO instance;
  return &instance;
}
void GLOBAL_SHAPE_PARTIDO::enter(ShapePartido* shapePartido)
{
}
void GLOBAL_SHAPE_PARTIDO::execute(ShapePartido* shapePartido)
{

}
void GLOBAL_SHAPE_PARTIDO::exit(ShapePartido* shapePartido)
{
}
bool GLOBAL_SHAPE_PARTIDO::onLetter(ShapePartido* shapePartido, Letter* letter)
{
        return false;
}


/*****************************************
*******       SHAPE PARTIDO STATES    ******************	
****************************************/

/*****************************************
	GAME_SHAPE_PARTIDO
****************************************/
GAME_SHAPE_PARTIDO* GAME_SHAPE_PARTIDO::Instance()
{
  static GAME_SHAPE_PARTIDO instance;
  return &instance;
}
void GAME_SHAPE_PARTIDO::enter(ShapePartido* shapePartido)
{
}
void GAME_SHAPE_PARTIDO::execute(ShapePartido* shapePartido)
{
	for (unsigned int i = 0; i < shapePartido->mClientPartido->mGamePartido->mBattleVector.size(); i++)
        {
                //if either of these is true than you you go to battle state
                if (shapePartido->mClientPartido->mGamePartido->mBattleVector.at(i)->mHomeCombatant->mClientPartido == shapePartido->mClientPartido)
                {
                	shapePartido->mShapePartidoStateMachine->changeState(BATTLE_SHAPE_PARTIDO::Instance());
                }
                if (shapePartido->mClientPartido->mGamePartido->mBattleVector.at(i)->mAwayCombatant->mClientPartido == shapePartido->mClientPartido)
                {
               		shapePartido->mShapePartidoStateMachine->changeState(BATTLE_SHAPE_PARTIDO::Instance());
                }
        }
}
void GAME_SHAPE_PARTIDO::exit(ShapePartido* shapePartido)
{
}
bool GAME_SHAPE_PARTIDO::onLetter(ShapePartido* shapePartido, Letter* letter)
{
        return false; 
}

/*****************************************
        BATTLE SHAPE       
****************************************/
BATTLE_SHAPE_PARTIDO* BATTLE_SHAPE_PARTIDO::Instance()
{
  static BATTLE_SHAPE_PARTIDO instance;
  return &instance; 
} 
void BATTLE_SHAPE_PARTIDO::enter(ShapePartido* shapePartido)
{
}       
void BATTLE_SHAPE_PARTIDO::execute(ShapePartido* shapePartido)
{
	bool inBattle = false;
 	for (unsigned int i = 0; i < shapePartido->mClientPartido->mGamePartido->mBattleVector.size(); i++)
        {
                if (shapePartido->mClientPartido->mGamePartido->mBattleVector.at(i)->mHomeCombatant->mClientPartido == shapePartido->mClientPartido)
                {
			inBattle = true;
                }
                if (shapePartido->mClientPartido->mGamePartido->mBattleVector.at(i)->mAwayCombatant->mClientPartido == shapePartido->mClientPartido)
                {
			inBattle = true;
                }
        }

	if (!inBattle)
	{
		shapePartido->mShapePartidoStateMachine->changeState(GAME_SHAPE_PARTIDO::Instance());	
	}

	shapePartido->mMove->mVelocity->zero();
}
void BATTLE_SHAPE_PARTIDO::exit(ShapePartido* shapePartido)
{

}
bool BATTLE_SHAPE_PARTIDO::onLetter(ShapePartido* shapePartido, Letter* letter)
{
	return false;	
}


