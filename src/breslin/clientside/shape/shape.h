#ifndef SHAPE_H
#define SHAPE_H

/**********************************
*          INCLUDES
**********************************/
//standard library
#include <string>
#include <vector>

//Ogre headers
#include "Ogre.h"
using namespace Ogre;

/**********************************
*          FORWARD DECLARATIONS
**********************************/
class Application;
class Vector3D;
class Ability;
class Game;
class Command;
class ByteBuffer;
class ObjectTitle;

class Shape
{
public:

Shape(Application* application, ByteBuffer* byteBuffer, bool isGhost);
~Shape();

/**************************************************
*			VARIABLES
**************************************************/
public:

//application
Application* mApplication;

//id
int   mIndex;

//speed
float mSpeed;
float mSpeedMax; 

//animate
bool mAnimate;

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

//OGRE_SPECIFIC_PRIVATE

//ghost
bool mIsGhost;

//ogre scene stuff
Entity*             mEntity;

//this is your pointer to move shape, really all you need.
SceneNode*          mSceneNode;

//billboard
ObjectTitle* mObjectTitle;
std::string  mObjectTitleString;

//scale
float mScale;


private:

//constants
static const char mCommandOriginX      = 4;
static const char mCommandOriginY      = 8;
static const char mCommandOriginZ      = 16;
static const char mCommandRotationX    = 32;
static const char mCommandRotationZ    = 64;

//mesh
int         mMeshCode;
std::string mMeshName;

//name
std::string mName;

/**************************************************
*			METHODS
**************************************************/

public:

//setting position
void     setPosition          (Vector3D*                  );
void     setPosition          (float x, float y, float z );

//setting rotation
void    setRotation(Vector3D* vector3D) ;

//getting position
Vector3D* getPosition          (                          ) ;
Vector3D* getRotation          (                          ) ;
//size
void     scale                (Vector3D                  ) ;

//visibility
void     setVisible           (bool b                    ) ;


//title
void     drawTitle            (                          ) ;
void     appendToTitle        (std::string appendage     ) ;
void     appendToTitle        (int appendage             ) ;
void     clearTitle           (                          ) ;

//dynamic
//abilitys
void     addAbility(Ability* ability);
Ability* getAbility(Ability* ability);

//movement
float       getDegreesToSomething(Vector3D* something                       ) ;
void        translate            (Vector3D* translateVector, int perspective) ;

//ticks
void processTick();
void interpolateTick(float renderTime);

//messaging
void readDeltaMoveCommand(ByteBuffer *mes);

//byteBuffer
void parseByteBuffer(ByteBuffer* byteBuffer);

//ghost
void moveGhostShape();

//OGRE_SPECIFIC_PRIVATE
//shape
void createShape();

//debugging
void checkExtents(Vector3D min);

//movement
void yaw        (float amountToYaw, bool converToDegree   );

//check rotation
Quaternion* getRotationTo(Vector3D* source, Vector3D* dest);

//title
void setupTitle();

//ogre scene node
SceneNode*  getSceneNode() { return mSceneNode; }

//utility
Ogre::Vector3 converToVector3(Vector3D* vector3d);

private:

//mesh
std::string getMeshString(int meshCode);
};

#endif
