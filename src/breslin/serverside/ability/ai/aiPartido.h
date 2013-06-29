#ifndef AIPARTIDO_H
#define AIPARTIDO_H

//parent
#include "../ai.h"

//Ogre headers
#include "Ogre.h"
using namespace Ogre;

class AIPartidoStateMachine;
class ShapePartido;

class AIPartido : public AI
{

public:

AIPartido(Shape* shape);
~AIPartido();

//ticks
void processTick    ();

ShapePartido* mShapePartido;

AIPartidoStateMachine* mAIPartidoStateMachine;

};

#endif

