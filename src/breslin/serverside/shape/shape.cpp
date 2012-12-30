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

#include <iostream>

#include <string>

Shape::Shape(unsigned int index, Game* game, Client* client, Vector3D* position, Vector3D* velocity, Vector3D* rotation, Ogre::Root* root,
			 bool animated ,bool collidable, float collisionRadius, int meshCode, bool ai)
{
	mPositionLast         = new Vector3D();
	
	mPositionBeforeCollision      = new Vector3D();

	mRotation         = new Vector3D();
	mRotationLast         = new Vector3D();

	mKey = 0;
	mKeyLast = 0;

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


	//*********add shape to db ****************/
	std::string one = "insert into shapes values (";
	
 	stringstream ss;//create a stringstream
   	ss << mIndex;//add number to the stream
    	std::string two = ss.str();//return a string with the contents of the stream

	std::string three = ",0.0,0.0,0.0,0.0,0.0,0.0)";
 
	std::string str;
	str.append(one);
	str.append(two);
	str.append(three);
	
	const char * c = str.c_str();
	mGame->sqlQuery(c);
	
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

	mPositionBeforeCollision->x = mSceneNode->getPosition().x;
    	mPositionBeforeCollision->y = mSceneNode->getPosition().y;
    	mPositionBeforeCollision->z = mSceneNode->getPosition().z;
	
	//process ticks on abilitys
	for (unsigned int i = 0; i < mAbilityVector.size(); i++)
	{
		mAbilityVector.at(i)->processTick();
	}

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

	if (client == mClient)
	{
		client->mMessage.WriteByte(1);
		LogString("write 1");
	}
	else
	{
		client->mMessage.WriteByte(0);
		LogString("write 0");
	}
	client->mMessage.WriteByte(mIndex);
			
	client->mMessage.WriteFloat(mSceneNode->getPosition().x);
	client->mMessage.WriteFloat(mSceneNode->getPosition().y);
	client->mMessage.WriteFloat(mSceneNode->getPosition().z);

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
	if(mSceneNode->getPosition().x != mPositionLast->x)
	{
		flags |= mCommandOriginX;
	}
	if(mSceneNode->getPosition().y != mPositionLast->y)
	{
		flags |= mCommandOriginY;
	}
	if(mSceneNode->getPosition().z != mPositionLast->z)
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

	if(mGame->mFrameTime != mGame->mFrameTimeLast)
	{
		flags |= mCommandFrameTime;
	}		
	return flags;
}

void Shape::addToMoveMessage(Message* message)
{
	int flags = setFlag();

	message->WriteByte(mIndex);

	// Flags
	message->WriteByte(flags);  

	//Origin
	if(flags & mCommandOriginX)
	{
		message->WriteFloat(mSceneNode->getPosition().x);
	}
	if(flags & mCommandOriginY)
	{
		message->WriteFloat(mSceneNode->getPosition().y);
	}
	if(flags & mCommandOriginZ)
	{
		message->WriteFloat(mSceneNode->getPosition().z);
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

	//frameTime
	if(flags & mGame->mCommandFrameTime)
	{
		message->WriteByte(mGame->mFrameTime);
	}
}

