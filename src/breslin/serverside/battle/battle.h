#ifndef BATTLE_H
#define BATTLE_H

#include "../../fsm/stateMachine.h"

class ClientPartido;

class Battle 
{

public:

Battle(ClientPartido* client1, ClientPartido* client2);
virtual ~Battle();

//update
void update();

StateMachine<Battle>* mStateMachine;
ClientPartido* mClient1;
ClientPartido* mClient2;


};

#endif

