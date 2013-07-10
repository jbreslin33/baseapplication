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

//handle message
virtual bool  handleMessage(const Telegram& msg);


Shape* mShape;
Shape* mSeekShape;
Vector3D* mSeekPoint;
void setSeekPoint(Vector3D* seekPoint);
void setSeekShape(Shape* seekShape);
void updateSeekPoint();

StateMachine<Seek>* mStateMachine;



};

#endif
