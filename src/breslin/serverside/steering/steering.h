#ifndef STEERING_H
#define STEERING_H

#include "../../baseentity/baseEntity.h"

#include "../../fsm/stateMachine.h"
#include "../../math/vector3D.h"

//Ogre headers
#include "Ogre.h"
using namespace Ogre;

class Shape;
class Vector3D;
class Letter;

class Steering : public BaseEntity 
{

public:

Steering(Shape* shape);
~Steering();

//update
virtual void update();

//handle letter 
virtual bool  handleLetter(Letter* letter);

Shape* mShape;
Shape* mSteeringShape;
Vector3D* mSteeringPoint;
void setSteeringPoint(Vector3D* steeringPoint);
void setSteeringShape(Shape* steeringShape);
void updateSteeringPoint();

StateMachine<Steering>* mStateMachine;

/*
buckland steering
*/
Vector3D* mSteeringForce;

//the current target (usually the ball or predicted ball position)
Vector3D* mTarget;

//the distance the player tries to interpose from the target
double mInterposeDist;

//multipliers. 
double mMultSeperation;

//how far it can 'see'
double mViewDistance;

  
//used by group behaviors to tag neighbours
bool         mTagged;

//Arrive makes use of these to determine how quickly a vehicle
//should decelerate to its target
enum deceleration{slow = 3, normal = 2, fast = 1};

//this behavior moves the agent towards a target position
Vector3D* seek(Vector3D* target);

//This behavior predicts where its prey will be and seeks
//to that location

Vector3D* pursuit(Shape* shape);
Vector3D* separation();

//this attempts to steer the agent to a position between the opponent
//and the object

Vector3D* interpose(Shape* shape, Vector3D* position, double distanceFromTarget);

//finds any neighbours within the view radius
void      findNeighbours();

bool accumulateForce(Vector3D* sf, Vector3D* forceToAdd);
  
Vector3D*  sumForces();

//a vertex buffer to contain the feelers rqd for dribbling
std::vector<Vector3D*> mAntenna;

Vector3D* calculate();

double forwardComponent();

//calculates the component of the steering force that is perpendicuar
//with the vehicle heading
double    sideComponent();

Vector3D* getForce(){ return mSteeringForce; }

Vector3D*  getTarget() { return mTarget; }
void       setTarget(Vector3D* target){ mTarget = target; }
double     interposeDistance() { return mInterposeDist; }
void       setInterposeDistance(double d){ mInterposeDist = d; }

bool mSeekOn;  
bool mSeperationOn;

};

#endif

