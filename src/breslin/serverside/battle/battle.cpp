#include "battle.h"
#include "../tdreamsock/dreamSockLog.h"
#include "../combatant/combatant.h"

#include <string>

//Ogre headers
#include "Ogre.h"
using namespace Ogre;

//steering states
#include "states/battleStates.h"

//shapes
#include "../client/robust/partido/clientPartido.h"

Battle::Battle(GamePartido* gamePartido, ClientPartido* homeClient, ClientPartido* awayClient)
{

	mGamePartido = gamePartido;

	//make 2 Combatants a home and away
	mHomeCombatant = new Combatant(this,homeClient);
	mAwayCombatant = new Combatant(this,awayClient);

	//set pointers to foes for combatants
	mHomeCombatant->mFoe = mHomeCombatant;
	mAwayCombatant->mFoe = mAwayCombatant;

	mBattleTime       = 0;
	mBattleStartTime  = 0;
	mBattleEndTime    = 0;
	mBattleLengthTime = 20000;

 	//battle states
	mStateMachine =  new StateMachine<Battle>(this);
	mStateMachine->setCurrentState      (INIT_BATTLE::Instance());
	mStateMachine->setPreviousState     (INIT_BATTLE::Instance());
	mStateMachine->setGlobalState       (GLOBAL_BATTLE::Instance());
}

Battle::~Battle()
{
	delete mStateMachine;
}
void Battle::update()
{
	mStateMachine->update();
	mHomeCombatant->update();
	mAwayCombatant->update();
}

