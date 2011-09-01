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

//dispatch
class Dispatch;

//ability
class Ability;

//parser
class Parser;

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

//game
Game* mGame;

//parser
Parser* mParser;

//speed
float mSpeed; 
float mSpeedMax; 

//abilitys
std::vector<Ability*> mAbilityVector;	 //all abilitys for this shape

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

//abilitys
void     addAbility(Ability* ability);
Ability* getAbility(Ability* ability);

//movement
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

//dispatch
void parseDispatch(Dispatch* dispatch);

//ghost
void moveGhostShape();


};

#endif

