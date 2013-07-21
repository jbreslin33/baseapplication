#include "computerPartido.h"
#include "../../tdreamsock/dreamSockLog.h"

#include "../../shape/partido/shapePartido.h"

#include <string>

//Ogre headers
#include "Ogre.h"
using namespace Ogre;

//computer states
#include "states/computerPartidoStates.h"

ComputerPartido::ComputerPartido(ShapePartido* shape) : Computer(shape)
{
	mShapePartido = shape;

 	//computer states
   	mComputerPartidoStateMachine = new StateMachine<ComputerPartido>(this);
	mComputerPartidoStateMachine->setCurrentState      (HUMAN_CONTROLLED_PARTIDO::Instance());
	mComputerPartidoStateMachine->setPreviousState     (HUMAN_CONTROLLED_PARTIDO::Instance());
	mComputerPartidoStateMachine->setGlobalState       (GLOBAL_COMPUTER_PARTIDO::Instance());

	mCounter   = 0;
        mThreshold = 1000;

	mTactic = 0;
}

ComputerPartido::~ComputerPartido()
{
}

void ComputerPartido::update()
{
	mComputerPartidoStateMachine->update();
}

bool ComputerPartido::handleLetter(Letter* letter)
{
	return Computer::handleLetter(letter);
}
// 0 = none, 1 = aggressive, 2 = scared, 3 = precise, 4 = sloppy
void ComputerPartido::setTactic(int tactic)
{
	mTactic = tactic;	
}
