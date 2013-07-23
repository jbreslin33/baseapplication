#ifndef SEEK_H
#define SEEK_H

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

class Seek : public BaseEntity 
{

public:

Seek(Shape* shape);
~Seek();

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

Shape* mSeekShape;
Shape* mDestinationShape;

Vector3D* mSeekPoint;
Vector3D* mDestinationPoint;

Vector3D* mSeekVelocity;
Vector3D* mDestinationVelocity;

float mSeekLength;
float mDestinationLength;

void setSeekPoint(Vector3D* seekPoint);
void setDestinationPoint(Vector3D* destinationPoint);

Vector3D* getSeekPoint() { return mSeekPoint; }
Vector3D* getDestinationPoint() { return mDestinationPoint; }

void setSeekShape(Shape* seekShape);
void setDestinationShape(Shape* destinationShape);

Shape* getSeekShape() { return mSeekShape; }
Shape* getDestinationShape() { return mDestinationShape; }

void updateSeekPoint();
void updateDestinationPoint();

StateMachine<Seek>* mStateMachine;


};

#endif

