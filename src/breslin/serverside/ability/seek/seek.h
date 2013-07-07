#ifndef SEEK_H
#define SEEK_H

/***********************************************
		METHODS
***********************************************/

//parent
#include "../ability.h"

//Ogre headers
#include "Ogre.h"
using namespace Ogre;

/***********************************************
		FORWARD DECLARATIONS
***********************************************/

class SeekStateMachine;
class Shape;
class Vector3D;

class Seek : public Ability
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

//ticks
void processTick    ();

Shape* mShape;
Shape* mSeekShape;
Vector3D* mSeekPoint;
void setSeekPoint(Vector3D* seekPoint);
void setSeekShape(Shape* seekShape);
void updateSeekPoint();

SeekStateMachine* mSeekStateMachine;



};

#endif

