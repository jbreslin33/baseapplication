#include "combatant.h"
#include "../tdreamsock/dreamSockLog.h"

#include <string>

//Ogre headers
#include "Ogre.h"
using namespace Ogre;

//states
#include "states/combatantStates.h"

//battle
#include "../battle/battle.h"

//shapes
#include "../client/robust/partido/clientPartido.h"

Combatant::Combatant(Battle* battle, ClientPartido* clientPartido)
{
	mBattle = battle;
	mClientPartido = clientPartido;
	mFoe = NULL;

 	//combatant states
	mStateMachine =  new StateMachine<Combatant>(this);
	mStateMachine->setCurrentState      (INIT_COMBATANT::Instance());
	mStateMachine->setPreviousState     (INIT_COMBATANT::Instance());
	mStateMachine->setGlobalState       (GLOBAL_COMBATANT::Instance());
}

Combatant::~Combatant()
{
	delete mStateMachine;
}

void Combatant::update()
{
	mStateMachine->update();
}

