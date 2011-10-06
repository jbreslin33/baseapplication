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
		LogString("add animation");
		addAbility(new AbilityAnimationOgre(this));
	}
	
	setupTitle();

	//call create ghost here..
	if (!mIsGhost) 
	{
		//create a ghost for this shape
		mGhost = new ShapeDynamicOgre(mGameOgre,byteBuffer,true);
		mGhost->setVisible(true);

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
		//this cube is exactly 1 ogre world unit. Which I take to be 1 meter.
		mScale = .01f;
		return "cube.mesh";
	}
	if (meshCode == 1)
	{
		mScale = .25f;
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
void ShapeDynamicOgre::setRotation(Vector3D* vector3D)
{
	Vector3 vec;
	vec.x = vector3D->x;
	vec.y = vector3D->y;
	vec.z = vector3D->z;
	getSceneNode()->setDirection(vec,Ogre::Node::TS_WORLD);
}

Vector3D* ShapeDynamicOgre::getRotation()
{
	Vector3D* vector3D = new Vector3D();
	
	vector3D->x = getSceneNode()->_getDerivedOrientation().zAxis().x * -1;
	vector3D->y = 0.0;
	vector3D->z = getSceneNode()->_getDerivedOrientation().zAxis().z * -1;

	return vector3D;
}

void ShapeDynamicOgre::yaw(float amountToYaw, bool convertToDegree)
{
	//LogString("a:%f",amountToYaw);
	if (convertToDegree)
	{
		getSceneNode()->yaw(Degree(amountToYaw));
		//1 = due west, -1 = due east, 0 = due south, -2 due east, 2 = due west
		Vector3 direction;
		direction.x = 1; //southwest
		direction.y = 0;
		direction.z = -1; 

		direction.normalise();
	}
}

//calculate how far off we are from some vector
float ShapeDynamicOgre::getDegreesToSomething(Vector3D* vectorOfSomething)
{
	//get the orientation of shape in the z axis
	Vector3 orientation;
	orientation = getSceneNode()->getOrientation().zAxis();
	
	Vector3D* orientation3D = new Vector3D();
	orientation3D->x = orientation.x;
	orientation3D->y = orientation.y;
	orientation3D->z = orientation.z;
	
	Quaternion* toSomething = getRotationTo(orientation3D,vectorOfSomething);
	
    // convert to degrees
    Real degreesToSomething = toSomething->getYaw().valueDegrees();
	
	return degreesToSomething;
}

void ShapeDynamicOgre::translate(Vector3D* translateVector, int perspective)
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

void ShapeDynamicOgre::setPosition(Vector3D* position)
{
	getSceneNode()->setPosition(converToVector3(position));
}

void ShapeDynamicOgre::setPosition(float x, float y, float z)
{
	getSceneNode()->setPosition(x,y,z);
}

Vector3D* ShapeDynamicOgre::getPosition()
{
	Vector3D* position = new Vector3D();
	position->x = getSceneNode()->getPosition().x;
	position->y = getSceneNode()->getPosition().y;
	position->z = getSceneNode()->getPosition().z;
	return position;
}

Ogre::Vector3 ShapeDynamicOgre::converToVector3(Vector3D* vector3d)
{
	Ogre::Vector3 vec3;
	vec3.x = vector3d->x;
	vec3.y = vector3d->y;
	vec3.z = vector3d->z;
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

Quaternion* ShapeDynamicOgre::getRotationTo(Vector3D* source, Vector3D* dest)
{
	Quaternion* quaternion = new Quaternion();

	Vector3D* fallbackAxis = new Vector3D(0.0f,1.0f,0.0f);

	Vector3D* v0 = new Vector3D();
	Vector3D* v1 = new Vector3D();
	v0->copyValuesFrom(source);
	v1->copyValuesFrom(dest);

	v0->normalise();	
	v1->normalise();

	//Real d = v0.dotProduct(v1);
	float d = v0->dot(v1);

    // If dot == 1, vectors are the same
    if (d >= 1.0f)
    {
		Quaternion* quaternionIdentity = new Quaternion(1.0,0.0,0.0,0.0);
		return quaternionIdentity;
    }
			
	if (d < (1e-6f - 1.0f))
	{
		// rotate 180 degrees about the fallback axis
		//Vector3 fb;
		//fb.x = fallbackAxis->x;
		//fb.y = fallbackAxis->y;
		//fb.z = fallbackAxis->z;
		//quaternion->FromAngleAxis(Radian(Math::PI), fb);
	}
	else
	{
		Real s = Math::Sqrt( (1+d)*2 );
        Real invs = 1 / s;

		Vector3D* c = v0->crossProduct(v1);

   	    quaternion->x = c->x * invs;
       	quaternion->y = c->y * invs;
        quaternion->z = c->z * invs;
        quaternion->w = s * 0.5f;
		quaternion->normalise();
	}
return quaternion;
}