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
	mComputerPartidoStateMachine->setCurrentState      (NULL);
	mComputerPartidoStateMachine->setPreviousState     (NULL);
	mComputerPartidoStateMachine->setGlobalState       (GlobalComputerPartido::Instance());

	mCounter   = 0;
        mThreshold = 1000;
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


