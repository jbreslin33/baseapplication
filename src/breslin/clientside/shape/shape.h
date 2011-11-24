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
class ApplicationBreslin;
class Vector3D;
class Ability;
class Game;
class Command;
class ByteBuffer;
class ObjectTitle;

class Shape
{
public:

Shape(ApplicationBreslin* applicationBreslin, ByteBuffer* byteBuffer, bool isGhost);
~Shape();

/**************************************************
*			VARIABLES
**************************************************/
public:

//applicationBreslin
ApplicationBreslin* mApplicationBreslin;

//id
int   mIndex;

//speed
float mSpeed;
float mSpeedMax; 

//this is used to rotate to and for debugging. it goes right to lates serverFrame from net.
Shape* mGhost;

//commands
Command* mServerCommandLast;
Command* mServerCommandCurrent;					// the latest frame from server
Command* mCommandToRunOnShape;

//ogre scene stuff
Entity*             mEntity;

//billboard
ObjectTitle* mObjectTitle;
std::string  mObjectTitleString;

protected:

int mLocal;

private:

//constants
static const char mCommandOriginX      = 4;
static const char mCommandOriginY      = 8;
static const char mCommandOriginZ      = 16;
static const char mCommandRotationX    = 32;
static const char mCommandRotationZ    = 64;

//spawn orientation
Vector3D* mSpawnPosition;
Vector3D* mSpawnRotation;

//mesh
int         mMeshCode;
std::string mMeshName;

//name
std::string mName;

//animate
bool mAnimate;

//abilitys
std::vector<Ability*> mAbilityVector;	 //all abilitys for this shape

//ghost
bool mIsGhost;

//scale
float mScale;

//this is your pointer to move shape, really all you need.
SceneNode*          mSceneNode;




/**************************************************
*			METHODS
**************************************************/

public:

//ogre scene node
SceneNode*  getSceneNode() { return mSceneNode; }

//process ByteBuffers
virtual void processDeltaByteBuffer(ByteBuffer* byteBuffer);

//setting position
void     setPosition          (Vector3D*                  );
void     setPosition          (float x, float y, float z );

//setting rotation
void    setRotation(Vector3D* vector3D) ;

//getting position
Vector3D* getPosition          (                          ) ;
Vector3D* getRotation          (                          ) ;

//title
void     appendToTitle        (std::string appendage     ) ;
void     appendToTitle        (int appendage             ) ;

//abilitys
void     addAbility(Ability* ability);
Ability* getAbility(Ability* ability);

//interpolation
void interpolateTick(float renderTime);

//ghost
void moveGhostShape();

//OGRE_SPECIFIC_PRIVATE
//shape
void spawnShape(Vector3D* position);

//debugging
void checkExtents(Vector3D min);

//movement
void yaw        (float amountToYaw, bool converToDegree   );

//title
void setupTitle();
void clearTitle() ;

protected:

// Parse ByteBuffers
virtual int parseDeltaByteBuffer(ByteBuffer *byteBuffer);

private:

//size
void     scale                (Vector3D                  ) ;

//visibility
void     setVisible           (bool b                    ) ;


//title
void     drawTitle            (                          ) ;

//mesh
std::string getMeshString(int meshCode);

//translate
void        translate            (Vector3D* translateVector, int perspective) ;

//process ByteBuffers
void processSpawnByteBuffer(ByteBuffer* byteBuffer);

// Parse ByteBuffers
void parseSpawnByteBuffer(ByteBuffer* byteBuffer);


};

#endif
