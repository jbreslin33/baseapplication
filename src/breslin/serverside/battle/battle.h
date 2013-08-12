#ifndef BATTLE_H
#define BATTLE_H

#include "../../fsm/stateMachine.h"

class ClientPartido;
class Combatant;

class Battle 
{

public:

Battle(ClientPartido* homeClient, ClientPartido* awayClient);
virtual ~Battle();

//update
void update();

StateMachine<Battle>* mStateMachine;

Combatant* mHomeCombatant;
Combatant* mAwayCombatant;

};

#endif

