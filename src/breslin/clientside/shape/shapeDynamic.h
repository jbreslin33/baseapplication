#ifndef DYNAMICSHAPE_H
#define DYNAMICSHAPE_H

#include "shape.h"

//command
#include "../../command/command.h"

//#include <string>

//game
class Game;

//state machines
class ShapeDynamicStateMachine;
class ShapeDynamicState;

class Dispatch;

//ability
class AbilityRotation;
class AbilityMove;
class AbilityAnimation;

class ShapeDynamic : public Shape //, public OgreAnimation
{

public:
ShapeDynamic(Game* game, Dispatch* dispatch);
~ShapeDynamic();

//network
//flag
static const char mCommandMilliseconds = 2;
static const char mCommandOriginX      = 4;
static const char mCommandOriginY      = 8;
static const char mCommandOriginZ      = 16;
static const char mCommandRotationX    = 32;
static const char mCommandRotationZ    = 64;

//abilitys
AbilityRotation* mAbilityRotation;
AbilityMove* mAbilityMove;
AbilityAnimation* mAbilityAnimation;

//this is used to rotate to and for debugging. it goes right to lates serverFrame from net.
ShapeDynamic* mGhost;

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

//virtual need to be implemented in subclass...
virtual void        yaw                  (float amountToYaw, bool converToDegree   ) = 0;
virtual float       getDegreesToSomething(Vector3D something                       ) = 0;
virtual void        translate            (Vector3D translateVector, int perspective) = 0;
virtual std::string getName() = 0; 

//ticks
void processTick();
void interpolateTick(float renderTime);

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

