#include "computerPartido.h"
#include "../../tdreamsock/dreamSockLog.h"

#include "../../shape/partido/shapePartido.h"
#include "../../game/partido/gamePartido.h"
#include "../../../math/vector3D.h"

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

ShapePartido* ComputerPartido::getClosestBattleShape()
{
        ShapePartido* closestShapeSoFar = NULL;
        float closestDistanceSoFar = 3000.0f;

        for (int i = 0; i < mShapePartido->mGamePartido->mShapePartidoVector.size(); i++)
        {
                ShapePartido* shape = mShapePartido->mGamePartido->mShapePartidoVector.at(i);
		if (shape == mShapePartido->mOpponentLast || shape == mShapePartido)
		{
			continue;
		}

                Vector3D* newKeyDirection         = new Vector3D();

                Vector3D* currentPosition         = new Vector3D();
                Vector3D* currentAvoideePosition  = new Vector3D();
                Vector3D* differenceVector        = new Vector3D();

                currentPosition->x = mShapePartido->mSceneNode->getPosition().x;
                currentPosition->y = mShapePartido->mSceneNode->getPosition().y;
                currentPosition->z = mShapePartido->mSceneNode->getPosition().z;

                currentAvoideePosition->x = shape->mSceneNode->getPosition().x;
                currentAvoideePosition->y = shape->mSceneNode->getPosition().y;
                currentAvoideePosition->z = shape->mSceneNode->getPosition().z;

                differenceVector->subtract(currentPosition,currentAvoideePosition);

                float length = differenceVector->length();

                if (length < closestDistanceSoFar)
                {
                        closestShapeSoFar = shape;
                        closestDistanceSoFar = length;
                }
        }
	return closestShapeSoFar;       
}

void ComputerPartido::getNewTactic()
{
	int dieroll = rand() % 100;
	
        if (dieroll > 0 && dieroll < 50)
        {
                mTactic = 1;
		return;
        }

        if (dieroll >=  50 && dieroll < 100)
        {
                mTactic = 2;
		return;
        }
}
