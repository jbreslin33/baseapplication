#include "shapeDynamicOgre.h"

//standard library
#include <string.h>

//log
#include "../tdreamsock/dreamSockLog.h"

//game
#include "../game/gameOgre.h"

//graphics
#include "../graphics/graphicsOgre.h"

//ability
#include "../ability/animation/abilityAnimationOgre.h"

//title
#include "../billboard/objectTitle.h"


ShapeDynamicOgre::ShapeDynamicOgre(GameOgre* gameOgre, ByteBuffer* byteBuffer, bool isGhost)
:
	ShapeDynamic         (gameOgre,byteBuffer)
{
	//we use this to name shape. as ogre is picky about same names. it also serves as a counter of sorts.

	mGameOgre = gameOgre;

	mIsGhost = isGhost;

	if (mIsGhost)
	{
		mIndex = mIndex * -1;
	}	

	//figure out mesh based on code passed in byteBuffer
	mMeshName = getMeshString(mMeshCode);
	

	createShape();
	
	//animation
	if (mAnimate)
	{
		addAbility(new AbilityAnimationOgre(this));
	}
	
	setupTitle();

	//call create ghost here..
	if (!mIsGhost) 
	{
		//create a ghost for this shape
		mGhost = new ShapeDynamicOgre(mGameOgre,byteBuffer,true);
		mGhost->setVisible(false);

		//put shape and ghost in game vectors so they can be looped and game now knows of them.
		mGame->mShapeVector.push_back(this);
		mGame->mShapeGhostVector.push_back(mGhost);	
	}


}

ShapeDynamicOgre::~ShapeDynamicOgre()
{
	delete mObjectTitle;
	//delete mEntity;
	delete mSceneNode;
}

std::string ShapeDynamicOgre::getMeshString(int meshCode)
{
	if (meshCode == 0)
	{
		mScale = 1;
		return "cube.mesh";
	}
	if (meshCode == 1)
	{
		mScale = 30 / 30;
		return "sinbad.mesh";
	}
}

void ShapeDynamicOgre::createShape()
{
	/*********  create shape ***************/
	//mMeshName     = mesh;
	mName         = StringConverter::toString(mIndex);
	mSceneNode    = mGameOgre->mGraphicsOgre->getSceneManager()->getRootSceneNode()->createChildSceneNode();

	//set Starting position of sceneNode, we will attach our mesh to this. this is all that's needed for static shapes. actually we need to add
	//rotation for them
	mSceneNode->setPosition(mPosition->x,mPosition->y,mPosition->z);	
	
	//create mesh
	mEntity = mGameOgre->mGraphicsOgre->getSceneManager()->createEntity(mName, mMeshName);

	//attache mesh to scenenode, henceforward we will use mSceneNode to control shape.
    mSceneNode->attachObject(mEntity);

	//for scale, won't be needed in future hopefully...
	Vector3D v;
	v.x = mScale;
	v.y = mScale;
	v.z = mScale;
	scale(v);
}

void ShapeDynamicOgre::setupTitle()
{
	/*********  setup title/billboard ***************/
	const Ogre::String& titlename = "tn" + StringConverter::toString(mIndex);
	const Ogre::String& title = "ti" + StringConverter::toString(mIndex);
	const Ogre::String& fontName = "SdkTrays/Caption";
	const Ogre::ColourValue& color = Ogre::ColourValue::White;
	mObjectTitle = new ObjectTitle
	(titlename, mEntity, mGameOgre->mGraphicsOgre->getSceneManager()->getCamera("PlayerCam"), title,
    fontName, color);
}

void ShapeDynamicOgre::scale(Vector3D scaleVector)
{
	getSceneNode()->scale(scaleVector.x, scaleVector.y, scaleVector.z);
}

void ShapeDynamicOgre::checkExtents(Vector3D min)
{

	Ogre::Vector3 max;
	max = Ogre::Vector3::UNIT_SCALE;

	assert( (min.x <= max.x && min.y <= max.y && min.z <= max.z) &&
                "you have a problem with a vector maybe dividing by zero or a garbage value!" );

			//mExtent = EXTENT_FINITE;
			//mMinimum = min;
			//mMaximum = max;
}

void ShapeDynamicOgre::yaw(float amountToYaw, bool convertToDegree)
{
	if (convertToDegree)
	{
		getSceneNode()->yaw(Degree(amountToYaw));
	}
}
float ShapeDynamicOgre::getDegreesToSomething(Vector3D vectorOfSomething)
{
    //calculate how far off we are from server
    Quaternion toSomething = getSceneNode()->getOrientation().zAxis().getRotationTo(converToVector3(vectorOfSomething),Vector3::UNIT_Y);

    // convert to degrees
    Real degreesToServer = toSomething.getYaw().valueDegrees();
	return degreesToServer;
}

//1 world, 2 local
void ShapeDynamicOgre::translate(Vector3D translateVector, int perspective)
{
	if (perspective == 1)
	{
		getSceneNode()->translate(converToVector3(translateVector), Ogre::Node::TS_WORLD);
	}
	if (perspective == 2)
	{
		getSceneNode()->translate(converToVector3(translateVector), Ogre::Node::TS_LOCAL);
	}
}

void ShapeDynamicOgre::setPosition(Vector3D position)
{
	getSceneNode()->setPosition(converToVector3(position));
}

void ShapeDynamicOgre::setPosition(float x, float y, float z)
{
	getSceneNode()->setPosition(x,y,z);
}

Vector3D ShapeDynamicOgre::getPosition()
{
	Vector3D position;
	position.x = getSceneNode()->getPosition().x;
	position.y = getSceneNode()->getPosition().y;
	position.z = getSceneNode()->getPosition().z;
	return position;
}

Ogre::Vector3 ShapeDynamicOgre::converToVector3(Vector3D vector3d)
{
	Ogre::Vector3 vec3;
	vec3.x = vector3d.x;
	vec3.y = vector3d.y;
	vec3.z = vector3d.z;
	return vec3;
}

void ShapeDynamicOgre::setVisible(bool visible)
{
	getSceneNode()->setVisible(visible);
}

//title

void ShapeDynamicOgre::drawTitle()
{
	mObjectTitle->setTitle(mObjectTitleString); 
	mObjectTitle->update();
}
void ShapeDynamicOgre::appendToTitle(std::string appendage)
{
	mObjectTitleString.append(appendage);
}

void ShapeDynamicOgre::appendToTitle(int appendage)
{
	mObjectTitleString.append(StringConverter::toString(appendage));
}

void ShapeDynamicOgre::clearTitle()
{
	mObjectTitleString.clear();
}