#include "gameGhostInTheGraveyard.h"

//log
#include "../tdreamsock/dreamSockLog.h"

//shape
#include "../shape/shape.h"

//client
#include "../client/client.h"

//math
#include "../../math/vector3D.h"

GameGhostInTheGraveyard::GameGhostInTheGraveyard()
{
	LogString("Hosting GameGhostInTheGraveyard");

	//ai guys, let's make them sinbads
	for(int i = 0; i < 1; i++)
	{                 
		Vector3D* position = new Vector3D();
		position->x = 5.0f;
		position->y = 0.0f;
		position->z = 2.0f * i;

		createAIShape(position, new Vector3D(), new Vector3D, true, true, .66f, 1, true);
	}
	

	//Grave1
/*
	Vector3D* position = new Vector3D();
	
	//east wall
	for (int i = -10; i < 10; i++)
	{
		//collidable static shapes with no animation for now it's a WALL
		Vector3D* position = new Vector3D();
		position->x = 10;
		position->y = 0;
		position->z = 1 * i;
		createAIShape(position, new Vector3D(), new Vector3D, false, true, .5, 0, false);
	}


	//west wall
	for (int i = -10; i < 10; i++)
	{
		//collidable static shapes with no animation for now it's a WALL
		Vector3D* position = new Vector3D();
		position->x = -10;
		position->y = 0;
		position->z = 1 * i;
		createAIShape(position,false,true,.5,0,false);
	}

	//north wall
	for (int i = -10; i < 10; i = i++)
	{
		//collidable static shapes with no animation for now it's a WALL
		Vector3D* position = new Vector3D();
		position->x = 1 * i;
		position->y = 0;
		position->z = -10;
		createAIShape(position, new Vector3D(), new Vector3D, false, true, .5, 0, false);
	}

	//south wall
	for (int i = -10; i < 10; i = i++)
	{
		//collidable static shapes with no animation for now it's a WALL
		Vector3D* position = new Vector3D();
		position->x = 1 * i;
		position->y = 0;
		position->z = 10;
		createAIShape(position, new Vector3D(), new Vector3D, false, true, .5, 0, false);
	}
*/
}

GameGhostInTheGraveyard::~GameGhostInTheGraveyard()
{
	
}

void GameGhostInTheGraveyard::createClientAvatar(Client* client, bool animated ,bool collidable, float collisionRadius, int meshCode, bool ai)
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
