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
