#ifndef AVOID_H
#define AVOID_H

#include "../../baseentity/baseEntity.h"

#include "../../fsm/stateMachine.h"

//Ogre headers
#include "Ogre.h"
using namespace Ogre;

class Shape;
class Vector3D;
class Letter;

class Avoid : public BaseEntity 
{

public:

Avoid(Shape* shape);
~Avoid();

//update
virtual void update();

//handle letter 
virtual bool  handleLetter(Letter* letter);

Shape* mShape;

void addAvoidShape   (Shape* avoidShape);
bool removeAvoidShape(Shape* avoidShape);

Vector3D* mAvoidVelocity;
float mAvoidLength;

StateMachine<Avoid>* mStateMachine;

std::vector<Shape*> mAvoidVector;

Shape* findClosestAvoidee();

};

#endif

