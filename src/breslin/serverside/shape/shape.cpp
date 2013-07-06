//parent
#include "shape.h"

//log
#include "../tdreamsock/dreamSockLog.h"

//network
#include "../network/network.h"

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

//seek
#include "../ability/seek/seek.h"

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

	mRotationBres         = new Vector3D();
	mRotationLast         = new Vector3D();

	mKey = 0;
	mKeyLast = 0;

 	//mPosition = position;
	mIndex  = index;

	//speed
	mSpeedMax = 1.66f;

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
	mCollisionRadiusSpawn = collisionRadius * 2;
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

	//add abilitys
	
	mAI = new AI(this);
	mAbilityVector.push_back(mAI);	
	
	mSeek = new Seek(this);
	mAbilityVector.push_back(mSeek);	
	
	mRotation = new Rotation(this);
	mAbilityVector.push_back(mRotation);	
	
	mMove = new Move(this);
	mAbilityVector.push_back(mMove);	

	
	//register with shape vector
	mGame->mShapeVector.push_back(this);
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

void Shape::collision(Shape* shape)
{
  	float x = mPositionBeforeCollision->x;
        float z = mPositionBeforeCollision->z;
        mSceneNode->setPosition(x,0.0,z);
}

void Shape::setValues()
{
	
}

void Shape::addAbility(Ability* ability)
{
	mAbilityVector.push_back(ability);	
}

void Shape::remove()
{
	//make mMessage on server then send it to each client in turn 
        for (unsigned int i = 0; i < mGame->mServer->mClientVector.size(); i++)
	{
		if (mGame->mServer->mClientVector.at(i)->mGame == mGame)
		{
			if (mGame->mServer->mClientVector.at(i)->mClientID > -1)
			{
				if (mGame->mServer->mClientVector.at(i)->mShape != this)
				{
 					mGame->mServer->mMessage.Init(mGame->mServer->mMessage.outgoingData, sizeof(mGame->mServer->mMessage.outgoingData));
       					mGame->mServer->mMessage.WriteByte(mGame->mServer->mMessageRemoveShape); // type
					if (mGame->mServer->mClientVector.at(i)->mClientID > 0)
					{
       						mGame->mServer->mMessage.WriteByte(mGame->mServer->mClientVector.at(i)->mClientID); //client id for browsers
					}
       					mGame->mServer->mMessage.WriteByte(mIndex);

					mGame->mServer->mNetwork->sendPacketTo(mGame->mServer->mClientVector.at(i),&mGame->mServer->mMessage);
					
				}
				else
				{
				}
			}
		}
        }

	//get rid of shape from games shape vector
	for (unsigned int i = 0; i < mGame->mShapeVector.size(); i++)
	{
		if (mGame->mShapeVector.at(i) == this)
		{
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

  	mRotationBres->x = mSceneNode->_getDerivedOrientation().zAxis().x;

    	mRotationBres->z = mSceneNode->_getDerivedOrientation().zAxis().z;

	if (mText.compare(mTextLast) != 0)
	{
		sendText();				
		mTextLast = mText;
	}
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
/*
	if (mClient->mLoggedIn)
	{
		LogString("x:%f",mKeyDirection.x);
		LogString("z:%f",mKeyDirection.z);
	}
*/

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
	if(mRotationBres->x != mRotationLast->x)
	{
		flags |= mCommandRotationX;
	}
	if(mRotationBres->z != mRotationLast->z)
	{
		flags |= mCommandRotationZ;
	}

	//if(mGame->mFrameTime != mGame->mFrameTimeLast)
	//{
	//	flags |= mCommandFrameTime;
	//}		
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
		message->WriteFloat(mRotationBres->x);
	}
	if(flags & mCommandRotationZ)
	{
		message->WriteFloat(mRotationBres->z);
	}

	//frameTime
	//if(flags & mGame->mCommandFrameTime)
	//{
	//	message->WriteByte(mGame->mFrameTime);
	//}
}

//to everyone
void Shape::setText(std::string text)
{
	mText.clear();
	mText.append(text);
/*
	mMessage.Init(mMessage.outgoingData, sizeof(mMessage.outgoingData));
       	mMessage.WriteByte(mMessageSetText); // add type

	//index id
	mMessage.WriteByte(mIndex);

	//username
       	int length = text.length();  
       	mMessage.WriteByte(length); //send length

       	//loop thru length and write it
       	for (int b=0; b < length; b++)
       	{
               	mMessage.WriteByte(text.at(b));
       	}
       	
	mGame->mServer->mNetwork->broadcast(&mMessage);
*/
}

void Shape::sendText()
{
	if (!mGame)
	{
		return;
	}

 	mMessage.Init(mMessage.outgoingData, sizeof(mMessage.outgoingData));
       	mMessage.WriteByte(mMessageSetText); // add type
	
	//index id
	mMessage.WriteByte(mIndex);

	//text
       	int length = mText.length();  
       	mMessage.WriteByte(length); //send length

       	//loop thru length and write it
       	for (int b=0; b < length; b++)
       	{
               	mMessage.WriteByte(mText.at(b));
       	}
	
       	mGame->mServer->mNetwork->broadcast(&mMessage);
}
