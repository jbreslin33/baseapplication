//parent
#include "shape.h"

//log
#include "../tdreamsock/dreamSockLog.h"

//game
#include "../game/game.h"

//client
#include "../../serverside/client/client.h"

//server
#include "../../serverside/server/server.h"

//rotation
#include "../ability/rotation/rotation.h"

//move
#include "../ability/move/move.h"

//ai
#include "../ability/ai/ai.h"

//math
#include "../../math/vector3D.h"


#include <string>

Shape::Shape(unsigned int index, Game* game, Client* client, Vector3D* position, Vector3D* velocity, Vector3D* rotation, Ogre::Root* root,
			 bool animated ,bool collidable, float collisionRadius, int meshCode, bool ai)
{
	mPosition         = new Vector3D();
	mPositionLast         = new Vector3D();
	
	mPositionBeforeCollision      = new Vector3D();

	mPositionVelocity = new Vector3D();

	mRotation         = new Vector3D();
	mRotationLast         = new Vector3D();

	mKey = 0;
	mKeyLast = 0;

	mMilliseconds = 19;

	mMillisecondsTotal = 0;
	mMillisecondsTotalLast = 0;

	mClientFrametime = 0.0f;

	//set values
	mPosition->copyValuesFrom(position);

 	//mPosition = position;
	mIndex  = index;

	//keys
    mKeyDirection = Vector3::ZERO;
	mKeyRotation  = 0.0f;
	mGoalDirection = Vector3::ZERO;

	//game
	mGame = game;

	//client -- if this shape has associated with it
	mClient = client;

	//mesh
	mMeshCode = meshCode;

	//collision
	mCollisionRadius = collisionRadius;
	mCollidable = collidable;

	//animated
	mAnimated = animated;

	//ai -- bool
	mIsAI = ai;

	//keys
	mKeyUp = 1;
	mKeyDown = 2;
	mKeyLeft = 4;
	mKeyRight = 8;
	mKeyCounterClockwise = 16;
	mKeyClockwise = 32;

	createShape(root,position);

	addAbilitys();

	//register with shape vector
	mGame->mShapeVector.push_back(this);

	sendShapeToClients();
	
}

Shape::~Shape()
{
	delete mSceneNode;
}

void Shape::createShape(Ogre::Root* root, Vector3D* position)
{
	//create ogre shape
	Ogre::SceneManager* mSceneManager = root->createSceneManager(Ogre::ST_GENERIC);

	//create node to represent shape on server and pass in spawnPoint
	mSceneNode = mSceneManager->getRootSceneNode()->createChildSceneNode(position->convertToVector3());
}

void Shape::setValues()
{
	
}

void Shape::sendShapeToClients()
{
	//send this shape to all clients
	for (unsigned int i = 0; i < mGame->mServer->mClientVector.size(); i++)
	{
		Client* clientToSendTo = mGame->mServer->mClientVector.at(i);
		
		//write it
		writeAdd(clientToSendTo);
		
		//send it
		clientToSendTo->SendPacket(&clientToSendTo->mMessage);
	}
}

void Shape::addAbility(Ability* ability)
{
	mAbilityVector.push_back(ability);	
}

void Shape::addAbilitys()
{
	//add abilitys
	addAbility(new Rotation(this));
	addAbility(new Move(this));
	if (mIsAI)
	{
		addAbility(new AI(this));
	}
}

Ability* Shape::getAbility(Ability* ability)
{
	for (unsigned int i = 0; i < mAbilityVector.size(); i++)
	{
		if (typeid(ability) == typeid(mAbilityVector.at(i)))
		{
			return mAbilityVector.at(i);
		}
	}
	return 0;
}


void Shape::remove()
{
	for (unsigned int i = 0; i < mGame->mShapeVector.size(); i++)
	{
		if (mGame->mShapeVector.at(i) == this)
		{
			mGame->mServer->sendRemoveShape(this);
			mGame->mShapeVector.erase (mGame->mShapeVector.begin()+i);
		}
	}
}

void Shape::processTick()
{
	setKeyDirection();

	//process ticks on abilitys
	for (unsigned int i = 0; i < mAbilityVector.size(); i++)
	{
		mAbilityVector.at(i)->processTick();
	}
	
	mPositionVelocity->x = mSceneNode->getPosition().x - mPosition->x;
    mPositionVelocity->y = mSceneNode->getPosition().y - mPosition->y;
    mPositionVelocity->z = mSceneNode->getPosition().z - mPosition->z;


	mPositionBeforeCollision->x = mPosition->x;
    mPositionBeforeCollision->y = mPosition->y;
    mPositionBeforeCollision->z = mPosition->z;

    mPosition->x = mSceneNode->getPosition().x;
    mPosition->y = mSceneNode->getPosition().y;
    mPosition->z = mSceneNode->getPosition().z;

	Ogre::Quaternion orientation = mSceneNode->getOrientation();
    Ogre::Vector3 vector = orientation * -Vector3::UNIT_Z;

  	mRotation->x = mSceneNode->_getDerivedOrientation().zAxis().x;

    mRotation->z = mSceneNode->_getDerivedOrientation().zAxis().z;
}

void Shape::setKeyDirection()  //this is called first in process tick so let's start conversion to separate
//move/rotation.
{
	mKeyDirection.x = 0;
    mKeyDirection.y = 0;
    mKeyDirection.z = 0;

	mKeyRotation = 0.0f;
    
	// keep track of the player's intended direction
    if(mKey & mKeyUp) 
	{
		mKeyDirection.z += -1;
	}

    if(mKey & mKeyLeft) 
	{
		mKeyDirection.x += -1;
	}
                
    if(mKey & mKeyDown) 
	{
        mKeyDirection.z += 1;
	}
    if(mKey & mKeyRight) 
	{
		mKeyDirection.x += 1;
	}

	mKeyDirection.normalise();


    // keep track of the player's intended rotation
    if(mKey & mKeyCounterClockwise) 
	{
		mKeyRotation += -1;
	}
    if(mKey & mKeyClockwise) 
	{
		mKeyRotation += 1;
	}
}

void Shape::writeAdd(Client* client)
{
	client->mMessage.Init(client->mMessage.outgoingData, sizeof(client->mMessage.outgoingData));

	client->mMessage.WriteByte(mGame->mServer->mAddShape); // type

	if (client->mShape == this)
	{
		client->mMessage.WriteByte(1);
	}
	else
	{
		client->mMessage.WriteByte(0);
	}
	client->mMessage.WriteByte(mIndex);
			
	client->mMessage.WriteFloat(mPosition->x);
	client->mMessage.WriteFloat(mPosition->y);
	client->mMessage.WriteFloat(mPosition->z);

	client->mMessage.WriteFloat(mRotation->x);
	client->mMessage.WriteFloat(mRotation->z);
			
	//mesh
	client->mMessage.WriteByte(mMeshCode);

	//animation
	client->mMessage.WriteByte(mAnimated);
}

int Shape::setFlag()
{
	int flags = 0;

	//Origin
	if(mPosition->x != mPositionLast->x)
	{
		flags |= mCommandOriginX;
	}
	if(mPosition->y != mPositionLast->y)
	{
		flags |= mCommandOriginY;
	}
	if(mPosition->z != mPositionLast->z)
	{
		flags |= mCommandOriginZ;
	}

	//Rotation
	if(mRotation->x != mRotationLast->x)
	{
		flags |= mCommandRotationX;
	}
	if(mRotation->z != mRotationLast->z)
	{
		flags |= mCommandRotationZ;
	}
	
	//Milliseconds
	if(mMillisecondsTotal != mMillisecondsTotalLast)
	{
		flags |= mCommandMilliseconds;
	}

	return flags;
}

void Shape::addToMoveMessage(Message* message)
{
	int flags = setFlag();

	message->WriteByte(mIndex);
	LogString("mIndex:%d",mIndex);

	// Flags
	message->WriteByte(flags);  

	//Origin
	if(flags & mCommandOriginX)
	{
		message->WriteFloat(mPosition->x);
	}
	if(flags & mCommandOriginY)
	{
		message->WriteFloat(mPosition->y);
	}
	if(flags & mCommandOriginZ)
	{
		message->WriteFloat(mPosition->z);
	}

	//Rotation
	if(flags & mCommandRotationX)
	{
		message->WriteFloat(mRotation->x);
	}
	if(flags & mCommandRotationZ)
	{
		message->WriteFloat(mRotation->z);
	}

	//Milliseconds
	if(flags & mGame->mCommandMilliseconds)
	{
		message->WriteByte(mMillisecondsTotal);
	}
}

