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
class Application;

//byteBuffer
class ByteBuffer;

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
ShapeDynamic(Application* application, ByteBuffer* byteBuffer);
~ShapeDynamic();

/************************************************
*                VARIABLES
*************************************************/

//game
Application* mApplication;

//mesh
int mMeshCode;

//animate
bool mAnimate;

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
Vector3D* mMoveVelocity;
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
virtual float       getDegreesToSomething(Vector3D* something                       ) = 0;
virtual void        yaw                  (float amountToYaw, bool converToDegree   ) = 0;
virtual void        translate            (Vector3D* translateVector, int perspective) = 0;
virtual std::string getName() = 0; 

//ticks
void processTick();
void interpolateTick(float renderTime);

//messaging
void virtual readDeltaMoveCommand(ByteBuffer *mes);

//byteBuffer
void parseByteBuffer(ByteBuffer* byteBuffer);

//ghost
void moveGhostShape();


};

#endif

