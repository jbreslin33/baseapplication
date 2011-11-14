#ifndef SHAPE_H
#define SHAPE_H

/**********************************
*          INCLUDES
**********************************/
//standard library
#include <string>
#include <vector>

/**********************************
*          FORWARD DECLARATIONS
**********************************/
class Application;
class Parser;
class Vector3D;
class Ability;
class Game;
class Command;
class ByteBuffer;

class Shape
{
public:

Shape(ByteBuffer* byteBuffer, bool isGhost);
~Shape();

/**************************************************
*			VARIABLES
**************************************************/
public:

//shape
ShapeOgre* mShapeOgre;

//id
int   mIndex;

//mesh
int         mMeshCode;
std::string mMeshName;

//name
std::string mName;

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
Shape* mGhost;

//basic
Vector3D* mPosition;
Vector3D* mMoveVelocity;
Vector3D* mRotation;
int mLocal;

//commands
Command* mServerFrame;					// the latest frame from server
Command* mCommandToRunOnShape;

/**************************************************
*			METHODS
**************************************************/


//setting position
virtual void     setPosition          (Vector3D*                  ) = 0;
virtual void     setPosition          (float x, float y, float z ) = 0;

//setting rotation
virtual void    setRotation(Vector3D* vector3D) = 0;

//getting position
virtual Vector3D* getPosition          (                          ) = 0;
virtual Vector3D* getRotation          (                          ) = 0;
//size
virtual void     scale                (Vector3D                  ) = 0;

//visibility
virtual void     setVisible           (bool b                    ) = 0;


//title
virtual void     drawTitle            (                          ) = 0;
virtual void     appendToTitle        (std::string appendage     ) = 0;
virtual void     appendToTitle        (int appendage             ) = 0;
virtual void     clearTitle           (                          ) = 0;

//dynamic
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
