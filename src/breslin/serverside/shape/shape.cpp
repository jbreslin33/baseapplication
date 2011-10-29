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
#include "../rotation/rotation.h"

//move
#include "../move/move.h"

//ai
#include "../ai/ai.h"

//ability


#include <string>

Shape::Shape(unsigned int index, Game* game, Client* client, Vector3D* position, Vector3D* velocity, Vector3D* rotation, Ogre::Root* root,
			 bool animated ,bool collidable, float collisionRadius, int meshCode, bool ai)
{

/****************ogreshape******/
Ogre::SceneManager* mSceneManager = root->createSceneManager(Ogre::ST_GENERIC);

	// set command origins
	mCommand.mPosition.x = position->x;
	mCommand.mPosition.y = position->y;
	mCommand.mPosition.z = position->z;

	//convert to ogre format
	Vector3 spawnPoint;
	spawnPoint.x = mCommand.mPosition.x;
	spawnPoint.y = mCommand.mPosition.y;
	spawnPoint.z = mCommand.mPosition.z;

	//create node to represent shape on server and pass in spawnPoint
	mSceneNode = mSceneManager->getRootSceneNode()->createChildSceneNode(spawnPoint);

 	mPosition = position;
	mIndex = 0;
	mIndex  = index;

	//keys
    mKeyDirection = Vector3::ZERO;
	mKeyRotation  = 0.0f;
	mGoalDirection = Vector3::ZERO;

	//abilitys
	//mRotation = new Rotation(this);
	//mMove = new Move(this);

	/*
	if (mIsAI)
	{
		mAI = new AI(this);
	}
	else
	{
		mAI = 0;
	}
*/
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

	mGame->mShapeVector.push_back(this);

	//send this shape to all clients
	for (unsigned int i = 0; i < mGame->mServer->mClientVector.size(); i++)
	{
		Client* clientToSendTo = mGame->mServer->mClientVector.at(i);
		
		//write it
		write(clientToSendTo);
		
		//send it
		clientToSendTo->SendPacket(&clientToSendTo->mMessage);
	}
	
}

Shape::~Shape()
{
	delete mSceneNode;
}


void Shape::addAbility(Ability* ability)
{
	
	mAbilityVector.push_back(ability);	
}

Ability* Shape::getAbility(Ability* ability)
{
	for (unsigned int i = 0; i < mAbilityVector.size(); i++)
	{
		//typeid(ability);

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

	/*
	//give ai a chance to jump in if this shape has not client
	if (mIsAI == true)
	{
		mAI->processTick();
	}

	mRotation->processTick();
	
	mMove->processTick();
	*/
	//process ticks on abilitys
	for (unsigned int i = 0; i < mAbilityVector.size(); i++)
	{
		mAbilityVector.at(i)->processTick();
	}
	
	mCommand.mPositionVelocity.x = mSceneNode->getPosition().x - mCommand.mPosition.x;
    mCommand.mPositionVelocity.y = mSceneNode->getPosition().y - mCommand.mPosition.y;
    mCommand.mPositionVelocity.z = mSceneNode->getPosition().z - mCommand.mPosition.z;

	mCommand.mPositionOld.x = mCommand.mPosition.x;
    mCommand.mPositionOld.z = mCommand.mPosition.z;
    mCommand.mPositionOld.y = mCommand.mPosition.y;

    mCommand.mPosition.x = mSceneNode->getPosition().x;
    mCommand.mPosition.y = mSceneNode->getPosition().y;
    mCommand.mPosition.z = mSceneNode->getPosition().z;

	Ogre::Quaternion orientation = mSceneNode->getOrientation();
    Ogre::Vector3 vector = orientation * -Vector3::UNIT_Z;

  	mCommand.mRotation.x = mSceneNode->_getDerivedOrientation().zAxis().x;

    mCommand.mRotation.z = mSceneNode->_getDerivedOrientation().zAxis().z;
}

void Shape::setKeyDirection()  //this is called first in process tick so let's start conversion to separate
//move/rotation.
{
	mKeyDirection.x = 0;
    mKeyDirection.y = 0;
    mKeyDirection.z = 0;

	mKeyRotation = 0.0f;
    
	// keep track of the player's intended direction
    if(mCommand.mKey & KEY_UP) 
	{
		mKeyDirection.z += -1;
	}

    if(mCommand.mKey & KEY_LEFT) 
	{
		mKeyDirection.x += -1;
	}
                
    if(mCommand.mKey & KEY_DOWN) 
	{
        mKeyDirection.z += 1;
	}
    if(mCommand.mKey & KEY_RIGHT) 
	{
		mKeyDirection.x += 1;
	}

	mKeyDirection.normalise();


    // keep track of the player's intended rotation
    if(mCommand.mKey & KEY_COUNTER_CLOCKWISE) 
	{
		mKeyRotation += -1;
	}
    if(mCommand.mKey & KEY_CLOCKWISE) 
	{
		mKeyRotation += 1;
	}
}

void Shape::write(Client* client)
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
			
	client->mMessage.WriteFloat(mCommand.mPosition.x);
	client->mMessage.WriteFloat(mCommand.mPosition.y);
	client->mMessage.WriteFloat(mCommand.mPosition.z);

	client->mMessage.WriteFloat(mCommand.mPositionVelocity.x);
	client->mMessage.WriteFloat(mCommand.mPositionVelocity.y);
	client->mMessage.WriteFloat(mCommand.mPositionVelocity.z);

	client->mMessage.WriteFloat(mCommand.mRotation.x);
	client->mMessage.WriteFloat(mCommand.mRotation.z);
			
	//mesh
	client->mMessage.WriteByte(mMeshCode);

	//animation
	client->mMessage.WriteByte(mAnimated);
}