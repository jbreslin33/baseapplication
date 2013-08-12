//parent
#include "combatantStates.h"

//log
#include "../../tdreamsock/dreamSockLog.h"

//combatant
#include "../combatant.h"

//client
#include "../../client/robust/partido/clientPartido.h"

/*****************************************
*******       GLOBAL    ******************
****************************************/
GLOBAL_COMBATANT* GLOBAL_COMBATANT::Instance()
{
  static GLOBAL_COMBATANT instance;
  return &instance;
}
void GLOBAL_COMBATANT::enter(Combatant* combatant)
{
}
void GLOBAL_COMBATANT::execute(Combatant* combatant)
{

}
void GLOBAL_COMBATANT::exit(Combatant* combatant)
{
}
bool GLOBAL_COMBATANT::onLetter(Combatant* combatant, Letter* letter)
{
        return true;
}

/*****************************************
	INIT_COMBATANT
****************************************/
INIT_COMBATANT* INIT_COMBATANT::Instance()
{
	static INIT_COMBATANT instance;
	return &instance;
}
void INIT_COMBATANT::enter(Combatant* combatant)
{
}
void INIT_COMBATANT::execute(Combatant* combatant)
{
	
//	combatant->mClient1->mCombatant = combatant;	
//	combatant->mClient2->mCombatant = combatant;	
/*
	if (mOpponent == NULL && mOpponentLast != shape)
        {
                if (mClientPartido)
                {
                        mOpponent = (ShapePartido*)shape;
                }
        }

        //reset
        mCollisionTimeoutCounter = mCollisionTimeout;
        mCollidable = false;
*/
}
void INIT_COMBATANT::exit(Combatant* combatant)
{
}
bool INIT_COMBATANT::onLetter(Combatant* combatant, Letter* letter)
{
        return true;
}


/*****************************************
	NORMAL_COMBATANT
****************************************/
NORMAL_COMBATANT* NORMAL_COMBATANT::Instance()
{
  static NORMAL_COMBATANT instance;
  return &instance;
}
void NORMAL_COMBATANT::enter(Combatant* combatant)
{
}
void NORMAL_COMBATANT::execute(Combatant* combatant)
{
}
void NORMAL_COMBATANT::exit(Combatant* combatant)
{
}
bool NORMAL_COMBATANT::onLetter(Combatant* combatant, Letter* letter)
{
        return true;
}

/*****************************************
	OVER_COMBATANT
****************************************/
OVER_COMBATANT* OVER_COMBATANT::Instance()
{
	static OVER_COMBATANT instance;
	return &instance;
}
void OVER_COMBATANT::enter(Combatant* combatant)
{
}
void OVER_COMBATANT::execute(Combatant* combatant)
{
}
void OVER_COMBATANT::exit(Combatant* combatant)
{
}
bool OVER_COMBATANT::onLetter(Combatant* combatant, Letter* letter)
{
        return true;
}
