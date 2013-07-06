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
class Seek;
class Vector3D;
class Ability;

class Shape
{

public:
Shape(unsigned int index, Game* game, Client* client, Vector3D* position, Vector3D* velocity, Vector3D* rotation, Ogre::Root* root,
	  bool animated, bool collidable, float collisionRadius, int meshCode, bool ai);
~Shape();

/*****************************************************
(unsigned int index, GamePartido* gamePartido, Client* client, Vector3D* position, Vector3D* velocity, Vector3D* rotation, Ogre::Root* root,
          bool animated, bool collidable, float collisionRadius, int meshCode, bool ai);

*				VARIABLES
********************************************************/

// ByteBufferes
static const char mCommandFrameTime = 2;

static const char mMessageRemoveShape = -104;
static const char mMessageSetText     = -66;

static const char mMessageNonDeltaFrame = 2;
static const char mMessageServerExit = 3;
static const char mMessageKeepAlive = 12;

//network flags
static const char mCommandOriginX      = 1;
static const char mCommandOriginY      = 2;
static const char mCommandOriginZ      = 4;
static const char mCommandRotationX    = 8;
static const char mCommandRotationZ    = 16;


//ogre scene stuff
SceneNode*          mSceneNode;

int			mIndex;

//message
Message	mMessage; //is this all i need to get information over the internets?

//keys
Vector3 mKeyDirection;
float   mKeyRotation;
Vector3 mGoalDirection;

//speed
float mSpeedMax;

//game
Game* mGame;

//abilitys
std::vector<Ability*> mAbilityVector;	 //all abilitys for this shape
Rotation* mRotation;
Move* 	  mMove;
Seek*     mSeek;
AI*       mAI;

//associated client if any
Client* mClient;

//mesh
int mMeshCode;

//collision
float mCollisionRadius;
float mCollisionRadiusSpawn;
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

Vector3D* mPositionLast;

Vector3D* mPositionBeforeCollision;            //origin of last frame/tick

int mKey;               //key pressed
int mKeyLast; 

/******************************************************
*				METHODS
********************************************************/

void remove();

//abilitys
void     addAbility(Ability* ability);

//create
void createShape(Ogre::Root* root, Vector3D* position);

//ticks
virtual void processTick();

void setKeyDirection();

void setValues();

void setText(std::string text);
void sendText();
std::string mText;
std::string mTextLast;

void insertIntoDB();

//collision
virtual void collision(Shape* shape);

	//delta move command
virtual int  setFlag();
virtual void addToMoveMessage(Message* message);
};

#endif
