#ifndef SHAPE_H
#define SHAPE_H

//Ogre headers
#include "Ogre.h"
using namespace Ogre;

//command
#include "../command/command.h"

//message
#include "../message/message.h"

#include <string>

//key defines prob should be changed to a variable if possible
#define KEY_UP					1
#define KEY_DOWN				2
#define KEY_LEFT				4
#define KEY_RIGHT				8
#define KEY_COUNTER_CLOCKWISE      16
#define KEY_CLOCKWISE              32

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

void remove();

//abilitys
void     addAbility(Ability* ability);
Ability* getAbility(Ability* ability);

//ticks
void processTick();

void setKeyDirection();

void write(Client* client);


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

/******OGRESHAPE*******/

//ogre scene stuff
SceneNode*          mSceneNode;

//stats
Vector3D* mPosition;

int			mIndex;

Command	mCommand;		// current frame's commands we are about to or are running this on shapes on server.
Command mLastCommand;   //this is the last command sent to clients and also that was ran on server

Message	mMessage; //is this all i need to get information over the internets?

//keys
Vector3 mKeyDirection;
float mKeyRotation;
Vector3 mGoalDirection;

Game* mGame;

//Rotation* mRotation;
//Move* mMove;
//AI* mAI;

};

#endif