#ifndef COMBATANT_H
#define COMBATANT_H

#include "../../fsm/stateMachine.h"

class Battle;
class ClientPartido;

class Combatant 
{

public:

Combatant(Battle* battle, ClientPartido* clientPartido);
virtual ~Combatant();

//update
void update();

StateMachine<Combatant>* mStateMachine;
Battle* mBattle;
ClientPartido* mClientPartido;
Combatant* mFoe;

};

#endif

