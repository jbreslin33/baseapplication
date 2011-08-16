#ifndef DYNAMICSHAPE_H
#define DYNAMICSHAPE_H

#include "shape.h"

//command
#include "../../command/command.h"

#include <string>

//i want a dynamic shape...this should be dynamic shape shape should hide ogreshape...
class Game;
class DynamicShapeStateMachine;
class DynamicShapeState;
class Dispatch;
class AnimationAbility;

class DynamicShape : public Shape //, public OgreAnimation
{

public:
DynamicShape(Game* game, Dispatch* dispatch);
~DynamicShape();

//network
//flag
static const char mCommandMilliseconds = 2;
static const char mCommandOriginX      = 4;
static const char mCommandOriginY      = 8;
static const char mCommandOriginZ      = 16;
static const char mCommandRotationX    = 32;
static const char mCommandRotationZ    = 64;

//state machines
DynamicShapeStateMachine* mMoveProcessTickStateMachine;
DynamicShapeStateMachine* mMoveInterpolateTickStateMachine;
DynamicShapeStateMachine* mRotationProcessTickStateMachine;
DynamicShapeStateMachine* mRotationInterpolateTickStateMachine;

//animation
AnimationAbility* mAnimationAbility;

//this is used to rotate to and for debugging. it goes right to lates serverFrame from net.
DynamicShape* mGhost;

//basic
Vector3D* mPosition;
Vector3D* mVelocity;
Vector3D* mRotation;
int mLocal;

//commands
Command	mServerFrame;					// the latest frame from server
Command mCommandToRunOnShape;

//time
float mRenderTime;

//run speed
float mRunSpeed; //move
float mRunSpeedMax; //move

//thresholds
float mTurnSpeed; //rot
float mPosInterpLimitHigh; //mov
float mPosInterpFactor; //mov

//deltas
float mDeltaX;  //mov
float mDeltaZ;  //mov
float mDeltaY; //mov
float mDeltaPosition; //mov

//rotation
float mServerRotSpeed;  //rot

float mRotInterpLimitHigh;  //rot
float mRotInterpLimitLow;  //rot
float mRotInterpIncrease;   //rot
float mRotInterpDecrease;  //rot

//rotation
Vector3D mServerRotOld;  //rot
Vector3D mServerRotNew;  //rot
float    mDegreesToServer;  //rot

//virtual need to be implemented in subclass...
virtual void        yaw                  (float amountToYaw, bool converToDegree   ) = 0;
virtual float       getDegreesToSomething(Vector3D something                       ) = 0;
virtual void        translate            (Vector3D translateVector, int perspective) = 0;
virtual std::string getName() = 0; 

//ticks
void processTick();
void interpolateTick(float renderTime);

//rotation
float getDegreesToServer();  //rot
void  calculateServerRotationSpeed();  //rot

//move
void calculateDeltaPosition();  //mov

//messaging
void readDeltaMoveCommand(Dispatch *mes);

//statemachines
void createStateMachines();

//commands
void initializeCommands(Vector3D* position, Vector3D* rotation);

//variables
void initializeVariables();

//dispatch
void parseDispatch(Dispatch* dispatch);

//ghost
void moveGhostShape();


};

#endif

