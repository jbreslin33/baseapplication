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
Shape* mAvoidee;

void addAvoidShape   (Shape* avoidShape);
bool removeAvoidShape(Shape* avoidShape);

Vector3D* mVectorToClosestAvoidee;
Vector3D* mAvoidVelocity;
Vector3D* mAvoidVelocityLast;
Vector3D* mCurrentPosition;
Vector3D* mAvoideePosition;

float mVectorToClosestAvoideeLength;
float mVectorToClosestAvoideeLengthLast;

float mAvoidDot;
float mAvoidDotLast; //use this to see if angle is getting closer or further.

bool mEvadeWithXPositive;
bool mEvadeWithZPositive;
bool mEvadeWithXNegative;
bool mEvadeWithZNegative;

StateMachine<Avoid>* mStateMachine;

std::vector<Shape*> mAvoidVector;
std::vector<Shape*> mClosestAvoidees;

Shape* findClosestAvoidee();
void calculateClosestAvoidees();

float mPanicDistance;
float getPanicDistance() { return mPanicDistance; }
void setPanicDistance(float panicDistance) { mPanicDistance = panicDistance; }

float mRandomAvoidDegrees;
};

#endif

