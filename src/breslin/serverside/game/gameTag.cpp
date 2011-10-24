#include "gameTag.h"

//log
#include "../tdreamsock/dreamSockLog.h"

//shape
#include "../shape/shape.h"

//client
#include "../client/client.h"

//math
#include "../../math/vector3D.h"

GameTag::GameTag()
{
	LogString("Hosting GameTag");

	//ai guys, let's make them sinbads
	for(int i = 0; i < 1; i++)
	{                 
		Vector3D* position = new Vector3D();
		position->x = 5.0f;
		position->y = 0.0f;
		position->z = 2.0f * i;

		Shape* shape = new Shape(this,0,new Vector3D(),new Vector3D(),new Vector3D(),
			mRoot,getOpenIndex(),true,true,.66f,1,true); 
	
		mItShape = mShapeVector.at(0);
	}
}

GameTag::~GameTag()
{
	
}

void GameTag::checkCollisions(void)
{
	for (unsigned int i = 0; i < mShapeVector.size(); i++)
	{
	  
		if (mShapeVector.at(i)->mCollidable == true)
		{
			for (unsigned int j = i+1; j < mShapeVector.size(); j++) 
			{
				if (mShapeVector.at(j)->mCollidable == true)
				{
					float x1 = mShapeVector.at(i)->mSceneNode->getPosition().x;
					float z1 = mShapeVector.at(i)->mSceneNode->getPosition().z;
					float x2 = mShapeVector.at(j)->mSceneNode->getPosition().x;
					float z2 = mShapeVector.at(j)->mSceneNode->getPosition().z;

					float distSq = pow((x1-x2),2) + pow((z1-z2),2);
					
					//i am simply adding the 2 collisionradius's of the 2 objects in question then comparing
					//to distSQ between them. IS this right or is it working by chance?
					if(distSq < mShapeVector.at(i)->mCollisionRadius + mShapeVector.at(j)->mCollisionRadius)
					{
						mShapeVector.at(i)->mCommand.mPosition = mShapeVector.at(i)->mCommand.mPositionOld;
						mShapeVector.at(j)->mCommand.mPosition = mShapeVector.at(j)->mCommand.mPositionOld;

						float x3 = mShapeVector.at(i)->mCommand.mPositionOld.x;
						float z3 = mShapeVector.at(i)->mCommand.mPositionOld.z;
						float x4 = mShapeVector.at(j)->mCommand.mPositionOld.x;
						float z4 = mShapeVector.at(j)->mCommand.mPositionOld.z;

						mShapeVector.at(i)->mSceneNode->setPosition(x3,0.0,z3);
						mShapeVector.at(j)->mSceneNode->setPosition(x4,0.0,z4);

						//let's make someone it
						if (mShapeVector.at(i) == mItShape)
						{
							mItShape = mShapeVector.at(j);
							LogString("IT:%d",j);
						}
						else if (mShapeVector.at(j) == mItShape)
						{
							mItShape = mShapeVector.at(i);
							LogString("IT:%d",i);
						}

					}
				}
			}
		}
	}
}

void GameTag::buildDeltaMoveCommand(Message* mes, Shape* shape)
{
	Command* command = &shape->mCommand;

	int flags = setFlag(command,shape);
	buildDeltaMoveMessage(command,flags,mes,shape);
}


int GameTag::setFlag(Command* command, Shape* shape)
{

	int flags = 0;

	//Origin
	if(shape->mLastCommand.mPosition.x != command->mPosition.x)
	{
		flags |= CMD_ORIGIN_X;
	}
	if(shape->mLastCommand.mPosition.y != command->mPosition.y)
	{
		flags |= CMD_ORIGIN_Y;
	}
	if(shape->mLastCommand.mPosition.z != command->mPosition.z)
	{
		flags |= CMD_ORIGIN_Z;
	}

	//Rotation
	if(shape->mLastCommand.mRotation.x != command->mRotation.x)
	{
		flags |= CMD_ROTATION_X;
	}
	if(shape->mLastCommand.mRotation.z != command->mRotation.z)
	{
		flags |= CMD_ROTATION_Z;
	}
	
	//Milliseconds
	if(shape->mLastCommand.mMillisecondsTotal != command->mMillisecondsTotal)
	{
		flags |= CMD_MILLISECONDS;
	}
	return flags;
}

void GameTag::buildDeltaMoveMessage(Command* command, int flags, Message* message, Shape* shape)
{
	message->WriteByte(shape->mIndex);

	// Flags
	message->WriteByte(flags);  

	//Origin
	if(flags & CMD_ORIGIN_X)
	{
		message->WriteFloat(command->mPosition.x);
	}
	if(flags & CMD_ORIGIN_Y)
	{
		message->WriteFloat(command->mPosition.y);
	}
	if(flags & CMD_ORIGIN_Z)
	{
		message->WriteFloat(command->mPosition.z);
	}

	//Rotation
	if(flags & CMD_ROTATION_X)
	{
		message->WriteFloat(command->mRotation.x);
		//LogString("x:%f",command->mRotation.x);

	}
	if(flags & CMD_ROTATION_Z)
	{
		message->WriteFloat(command->mRotation.z);
		//LogString("z:%f",command->mRotation.z);
	}

	//Milliseconds
	if(flags & CMD_MILLISECONDS)
	{
		message->WriteByte(command->mMillisecondsTotal);
	}
}

