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

		createAIShape(position, new Vector3D(), new Vector3D, true, true, .66f, 1, true);
		mItShape = mShapeVector.at(0);
	}
}

GameTag::~GameTag()
{
	
}

void GameTag::createClientAvatar(Client* client, bool animated ,bool collidable, float collisionRadius, int meshCode, bool ai)
{
	Vector3D* pos = new Vector3D();
	pos->x = 0;
	pos->y = 0;
	pos->z = 0;

	Vector3D* vel = new Vector3D();
	vel->x = 0;
	vel->y = 0;
	vel->z = 0;

	Vector3D* rot = new Vector3D();
	rot->x = 0;
	rot->z = 0;

	Shape* shape = new Shape(pos,vel,rot,mRoot,getOpenIndex(),animated,collidable,collisionRadius,meshCode,ai); 
	shape->mGame = this; //for now to give access to shapeVector for collision i guess
	mShapeVector.push_back(shape); //either way add this to shape vector

	if (client != NULL)
	{
		client->mShape = shape; 
		client->mShape->mClient = client; //set client it could be NULL meaning just a serverside shape
	}
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

