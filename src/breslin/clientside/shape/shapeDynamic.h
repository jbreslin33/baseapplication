#ifndef DYNAMICSHAPE_H
#define DYNAMICSHAPE_H

/***************************************
*           INCLUDES
***************************************/
//standard library
#include <vector>

//parent
#include "shape.h"

//command
#include "../command/command.h"

/***************************************
*           FORWARD DECLARATIONS
***************************************/

//game
class Game;

//state machines
class ShapeDynamicStateMachine;
class ShapeDynamicState;

class Dispatch;

//ability
class Ability;
class AbilityRotation;
class AbilityMove;
class AbilityAnimation;

/**********************************
*          CLASS
**********************************/
class ShapeDynamic : public Shape
{

public:
ShapeDynamic(Game* game, Dispatch* dispatch);
~ShapeDynamic();

/************************************************
*                VARIABLES
*************************************************/

Game* mGame;

//speed
float mSpeed; 
float mSpeedMax; 

//network flags
static const char mCommandOriginX      = 4;
static const char mCommandOriginY      = 8;
static const char mCommandOriginZ      = 16;
static const char mCommandRotationX    = 32;
static const char mCommandRotationZ    = 64;

//abilitys
std::vector<Ability*> mAbilityVector;	 //all abilitys for this shape
AbilityAnimation* mAbilityAnimation;

//this is used to rotate to and for debugging. it goes right to lates serverFrame from net.
ShapeDynamic* mGhost;

//basic
Vector3D* mPosition;
Vector3D* mVelocity;
Vector3D* mRotation;
int mLocal;

//commands
Command* mServerFrame;					// the latest frame from server
Command* mCommandToRunOnShape;

/*************************************************
*				METHODS
**************************************************/

//virtual need to be implemented in subclass...

//abilitys
void     addAbility(Ability* ability);
Ability* getAbility(Ability* ability);

virtual void        yaw                  (float amountToYaw, bool converToDegree   ) = 0;
virtual float       getDegreesToSomething(Vector3D something                       ) = 0;
virtual void        translate            (Vector3D translateVector, int perspective) = 0;
virtual std::string getName() = 0; 
virtual float       getSpeed();

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

