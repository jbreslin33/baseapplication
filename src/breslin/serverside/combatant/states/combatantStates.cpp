//parent
#include "combatantStates.h"

//log
#include "../../tdreamsock/dreamSockLog.h"

//combatant
#include "../combatant.h"

//client
#include "../../client/robust/partido/clientPartido.h"

//server
#include "../../server/partido/serverPartido.h"

//battle
#include "../../battle/battle.h"
#include "../../battle/states/battleStates.h"

//shape
#include "../../shape/partido/shapePartido.h"

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
	//LogString("INIT_COMBAT:%d:",combatant->mClientPartido->id);
}
void INIT_COMBATANT::execute(Combatant* combatant)
{
	//we are ready to go if we have a foe
	if (combatant->mBattle->mStateMachine->currentState() == NORMAL_BATTLE::Instance())
	{
		//let internet client know to start a battle
		combatant->mClientPartido->sendSimpleMessage(combatant->mClientPartido->mServerPartido->mMessageBattleStart);
                combatant->mStateMachine->changeState(NORMAL_COMBATANT::Instance());
	}               
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
	//LogString("NORMAL_COMBATANT:%d:",combatant->mClientPartido->id);
}
void NORMAL_COMBATANT::execute(Combatant* combatant)
{
	if (combatant->mBattle->mStateMachine->currentState() == OVER_BATTLE::Instance())
	{
		//let internet client know to start a battle
		combatant->mClientPartido->sendSimpleMessage(combatant->mClientPartido->mServerPartido->mMessageBattleEnd);
                combatant->mStateMachine->changeState(YIELD::Instance());
	}
}
void NORMAL_COMBATANT::exit(Combatant* combatant)
{
}
bool NORMAL_COMBATANT::onLetter(Combatant* combatant, Letter* letter)
{
        return true;
}

/*****************************************
             YIELD 
****************************************/
YIELD* YIELD::Instance()
{
        static YIELD instance;
        return &instance;
}
void YIELD::enter(Combatant* combatant)
{
	LogString("YIELD:%d:",combatant->mClientPartido->id);
 	//reset opponent pointers and vars for answers...
/*
        mBattleScore      = 0;

        mQuestionString   = "";

        //relieve your last opponents last opponent if it was you
        if (mShapePartido->mOpponentLast)
        {
                if (mShapePartido->mOpponentLast->mOpponentLast == mShapePartido)
                {
                        mShapePartido->mOpponentLast->mOpponentLast = NULL;
                }
        }

        //set your last opponent
        mShapePartido->mOpponentLast = mShapePartido->mOpponent;

        //clear you opponent
        mShapePartido->mOpponent = NULL;

        mShapePartido->mCollidable = true;
*/
}
void YIELD::execute(Combatant* combatant)
{
	//stand down and do nothing or change cleanup
}
void YIELD::exit(Combatant* combatant)
{
}
bool YIELD::onLetter(Combatant* combatant, Letter* letter)
{
        return true;
}
