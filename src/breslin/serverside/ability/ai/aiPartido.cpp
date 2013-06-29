#include "ai.h"
#include "../../tdreamsock/dreamSockLog.h"

#include "../../client/client.h"

#include <string>

//Ogre headers
#include "Ogre.h"
using namespace Ogre;

//ai states
#include "states/aiStateMachine.h"
#include "states/aiStates.h"

AIPartido::AIPartido(ShapePartido* shapePartido) : AI(shapePartido)
{
	mShapePartido = shapePartido;

 	//ai states
	mAIPartidoStateMachine = new AIPartidoStateMachine(this);    //setup the state machine
	mAIPartidoStateMachine->setCurrentState      (Random_AI::Instance());
	mAIPartidoStateMachine->setPreviousState     (Random_AI::Instance());
	mAIPartidoStateMachine->setGlobalState       (NULL);
}

AIPartido::~AIPartido()
{
}
void AI::processTick()
{
	AI::processTick();
	mAIPartidoStateMachine->update();
}


