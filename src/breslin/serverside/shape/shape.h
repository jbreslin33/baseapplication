#ifndef SHAPE_H
#define SHAPE_H

//Ogre headers
#include "Ogre.h"
using namespace Ogre;

//message
#include "../message/message.h"

#include <string>

//forward declarations
class Game;
class Client;
class Rotation;
class Move;
class AI;
class Vector3D;
class Ability;

class Shape
{

public:
Shape(unsigned int index, Game* game, Client* client, Vector3D* position, Vector3D* velocity, Vector3D* rotation, Ogre::Root* root,
	  bool animated, bool collidable, float collisionRadius, int meshCode, bool ai);
~Shape();

/******************************************************
*				VARIABLES
********************************************************/

// ByteBufferes
static const char mCommandKey          = 1;
static const char mCommandMilliseconds = 2;


static const char mMessageConnect     = -101;
static const char mMessageDisconnect  = -102;
static const char mMessageAddShape    = -103;
static const char mMessageRemoveShape = -104;

static const char mMessageNonDeltaFrame = 2;
static const char mMessageServerExit = 3;
static const char mMessageKeepAlive = 12;

//network flags
static const char mCommandOriginX      = 4;
static const char mCommandOriginY      = 8;
static const char mCommandOriginZ      = 16;
static const char mCommandRotationX    = 32;
static const char mCommandRotationZ    = 64;


//ogre scene stuff
SceneNode*          mSceneNode;

int			mIndex;

//message
Message	mMessage; //is this all i need to get information over the internets?

//keys
Vector3 mKeyDirection;
float   mKeyRotation;
Vector3 mGoalDirection;

//game
Game* mGame;

//abilitys
std::vector<Ability*> mAbilityVector;	 //all abilitys for this shape

//associated client if any
Client* mClient;

//mesh
int mMeshCode;

//collision
float mCollisionRadius;
bool  mCollidable;

//animation
bool mAnimated;

//ai
bool mIsAI;

//keys
int mKeyUp;
int mKeyDown;
int mKeyLeft;
int mKeyRight;
int mKeyCounterClockwise;
int mKeyClockwise;

Vector3D* mPosition;            //finish origin of frame/tick
Vector3D* mPositionLast;

Vector3D* mPositionBeforeCollision;            //origin of last frame/tick

Vector3D* mPositionVelocity;	         //velocity during frame/tick

Vector3D* mRotation; //rotation during frame/tick
Vector3D* mRotationLast;

int mKey;               //key pressed
int mKeyLast; 

int mMilliseconds;      //not used

int mMillisecondsTotal;      //not used
int mMillisecondsTotalLast;

float mClientFrametime;

/******************************************************
*				METHODS
********************************************************/

void remove();

//abilitys
void     addAbility(Ability* ability);
Ability* getAbility(Ability* ability);
void addAbilitys();

//create
void createShape(Ogre::Root* root, Vector3D* position);

//ticks
void processTick();

void setKeyDirection();

void setValues();

void write(Client* client);

void sendShapeToClients();

	//delta move command
	virtual void buildDeltaMoveCommand(Message *mes);
	virtual int  setFlag();
	virtual void buildDeltaMoveMessage(int flags, Message* message);
};

#endif