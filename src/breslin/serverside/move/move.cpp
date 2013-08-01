#include "move.h"
#include "../tdreamsock/dreamSockLog.h"

#include "../client/client.h"

#include <string>

//Ogre headers
#include "Ogre.h"
using namespace Ogre;

#include "../../math/vector3D.h"

//move states
#include "states/moveStates.h"

Move::Move(Shape* shape) : BaseEntity(BaseEntity::getNextValidID())
{
        mVelocity = new Vector3D();

	mShape = shape;

	mPositionLast = new Vector3D();
	mPositionBeforeCollision = new Vector3D();

    	//runSpeed
    	mRunSpeed     = 0.0;

	//max speed
	mSpeedMax = 1.66f;

    	//run acceleration
    	mRunAccel    = .04166f * 30.5;
    	mRunDecel    = .04166f * 30.5;

	//max force
	mMaxForce = 1.0f;

 	//move states
	mStateMachine =  new StateMachine<Move>(this);
	mStateMachine->setCurrentState      (Normal_Move::Instance());
	mStateMachine->setPreviousState     (Normal_Move::Instance());
	mStateMachine->setGlobalState       (NULL);
}

Move::~Move()
{
	LogString("Move::~Move");
	delete mVelocity;
	delete mStateMacine;
	delete mPositionLast;
	delete mPositionBeforeCollision;
}
void Move::update()
{
	mStateMachine->update();
}

bool Move::handleLetter(Letter* letter)
{
        return mStateMachine->handleLetter(letter);
}



