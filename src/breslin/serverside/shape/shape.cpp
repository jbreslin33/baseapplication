#include "shape.h"
#include "../tdreamsock/dreamSockLog.h"

#include "../../serverside/client/client.h"
#include "../../serverside/server/server.h"

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
	mRotation = new Rotation(this);
	mMove = new Move(this);

	if (mIsAI)
	{
		mAI = new AI(this);
	}
	else
	{
		mAI = 0;
	}

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

	//give ai a chance to jump in if this shape has not client
	if (mIsAI == true)
	{
		//AI::processTick();
		mAI->processTick();
	}

	//don't do any rotation if there is no mKey set
	//should we though? we do it for movement below
	//does rotation not get to do the same?
	//is this why the rotation gets off???
	//UPDATE--I now check for mKey inside Rotation State machine
    
	//Rotation::processTick();
	mRotation->processTick();
	//even though there is no mKey set we still need to move as
	//brian has put in a deceleration factor so let's let it run...
	//Move::processTick();
	mMove->processTick();
	
	//set all vars to be sent off to clients playing on internets
	//none of this actually moves anything on server it is what is
	//going to be sent to clients so it's not in move or rotation.
	//though it could be i guess, velocity and position could go in move
	//and mRot could go in rotation.
    mCommand.mPositionVelocity.x = mSceneNode->getPosition().x - mCommand.mPosition.x;
    mCommand.mPositionVelocity.y = mSceneNode->getPosition().y - mCommand.mPosition.y;
    mCommand.mPositionVelocity.z = mSceneNode->getPosition().z - mCommand.mPosition.z;

	//mCommand.mPositionVelocity.normalise();

	mCommand.mPositionOld.x = mCommand.mPosition.x;
    mCommand.mPositionOld.z = mCommand.mPosition.z;
    mCommand.mPositionOld.y = mCommand.mPosition.y;

    mCommand.mPosition.x = mSceneNode->getPosition().x;
    mCommand.mPosition.y = mSceneNode->getPosition().y;
    mCommand.mPosition.z = mSceneNode->getPosition().z;

	Ogre::Quaternion orientation = mSceneNode->getOrientation();
    Ogre::Vector3 vector = orientation * -Vector3::UNIT_Z;

    //mCommand.mRotation.x = mSceneNode->getOrientation().zAxis().x;
    //mCommand.mRotation.z = mSceneNode->getOrientation().zAxis().z;

	mCommand.mRotation.x = mSceneNode->_getDerivedOrientation().zAxis().x;

    mCommand.mRotation.z = mSceneNode->_getDerivedOrientation().zAxis().z;
	//LogString("z:%f",mCommand.mRotation.z);
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