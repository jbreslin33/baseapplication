#include "ogreShape.h"
#include "../tdreamsock/dreamSockLog.h"

//math
#include "../../math/vector3D.h"

OgreShape::OgreShape()
{
}

//this is the contructor for server side ogre shape
OgreShape::OgreShape(Vector3D* position, Vector3D* velocity, Vector3D* rotation, Ogre::Root* root)
{
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
	mIndex  = index;

	//keys
    mKeyDirection = Vector3::ZERO;
	mKeyRotation  = 0.0f;
	mGoalDirection = Vector3::ZERO;

	mGame = NULL;
}

OgreShape::~OgreShape()
{
	//delete mSceneManager;
	delete mSceneNode;
}

