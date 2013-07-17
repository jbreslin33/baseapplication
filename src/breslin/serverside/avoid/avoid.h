#ifndef AVOID_H
#define AVOID_H

#include "../../baseentity/baseEntity.h"

#include "../../fsm/stateMachine.h"

//Ogre headers
#include "Ogre.h"
using namespace Ogre;

/***********************************************
		FORWARD DECLARATIONS
***********************************************/

class Shape;
class Vector3D;
class Letter;

class Avoid : public BaseEntity 
{

public:

Avoid(Shape* shape);
~Avoid();

/***********************************************
		VARIABLES
***********************************************/

/***********************************************
		METHODS
***********************************************/

//update
virtual void update();

//handle letter 
virtual bool  handleLetter(Letter* letter);


Shape* mShape;
Shape* mAvoidShape;
Vector3D* mAvoidPoint;
void setAvoidPoint(Vector3D* avoidPoint);
void setAvoidShape(Shape* avoidShape);
void updateAvoidPoint();

StateMachine<Avoid>* mStateMachine;



};

#endif

