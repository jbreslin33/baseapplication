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
void addAbilitys();

//create
void createShape(Ogre::Root* root, Vector3D* position);

//ticks
void processTick();

void setKeyDirection();

void setValues();

void write(Client* client);

void sendShapeToClients();

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

/******OGRESHAPE*******/

//ogre scene stuff
SceneNode*          mSceneNode;

//stats
Vector3D* mPosition;

int			mIndex;

Command*	mCommand;		// current frame's commands we are about to or are running this on shapes on server.
Command* mLastCommand;   //this is the last command sent to clients and also that was ran on server

Message	mMessage; //is this all i need to get information over the internets?

//keys
Vector3 mKeyDirection;
float mKeyRotation;
Vector3 mGoalDirection;

Game* mGame;

};

#endif