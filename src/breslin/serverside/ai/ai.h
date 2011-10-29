#ifndef SERVERSIDEAI_H
#define SERVERSIDEAI_H

//Ogre headers
#include "Ogre.h"
using namespace Ogre;

class Command;
class AIStateMachine;
class Shape;

class AI 
{

public:

AI(Shape* shape);
~AI();

//ticks
void processTick    ();

Shape* mShape;

AIStateMachine* mAIStateMachine;

};

#endif

