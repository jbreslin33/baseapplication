#ifndef BATTLE_H
#define BATTLE_H

#include "../../fsm/stateMachine.h"

class Shape;

class Battle 
{

public:

Battle(Shape* shape1, Shape* shape2);
virtual ~Battle();

//update
void update();

StateMachine<Battle>* mStateMachine;
Shape* mShape1;
Shape* mShape2;


};

#endif

