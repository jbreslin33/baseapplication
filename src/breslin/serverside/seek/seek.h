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
Vector3D* mSeekPoint;
Vector3D* mSeekVelocity;
float mSeekLength;
void setSeekPoint(Vector3D* seekPoint);
Vector3D* getSeekPoint() { return mSeekPoint; }
void setSeekShape(Shape* seekShape);
Shape* getSeekShape() { return mSeekShape; }
void updateSeekPoint();

StateMachine<Seek>* mStateMachine;


};

#endif

