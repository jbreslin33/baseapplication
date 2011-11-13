#include "shapeOgre.h"

//standard library
#include <string.h>

//log
#include "../tdreamsock/dreamSockLog.h"

//application
#include "../game/applicationOgre.h"

//gameOgre
#include "../game/gameOgre.h"

//graphics
#include "../graphics/graphicsOgre.h"

//ability
#include "../ability/animation/abilityAnimationOgre.h"

//title
#include "../billboard/objectTitle.h"


ShapeOgre::ShapeOgre(GameOgre* gameOgre, ByteBuffer* byteBuffer, bool isGhost)
:
	ShapeDynamic         ((Game*)gameOgre,byteBuffer)
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
		mGhost = new ShapeOgre(mGameOgre,byteBuffer,true);
		mGhost->setVisible(true);

		//put shape and ghost in game vectors so they can be looped and game now knows of them.
		mGameOgre->mShapeVector.push_back(this);
		mGameOgre->mShapeGhostVector.push_back(mGhost);	
	}
}

ShapeOgre::~ShapeOgre()
{
	delete mObjectTitle;
	//delete mEntity;
	delete mSceneNode;
}

std::string ShapeOgre::getMeshString(int meshCode)
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

void ShapeOgre::createShape()
{
	/*********  create shape ***************/
	//mMeshName     = mesh;
	mName         = StringConverter::toString(mIndex);
	mSceneNode    = mGameOgre->mApplicationOgre->getSceneManager()->getRootSceneNode()->createChildSceneNode();

	//set Starting position of sceneNode, we will attach our mesh to this. this is all that's needed for static shapes. actually we need to add
	//rotation for them
	mSceneNode->setPosition(mPosition->x,mPosition->y,mPosition->z);	
	
	//create mesh
	mEntity = mGameOgre->mApplicationOgre->getSceneManager()->createEntity(mName, mMeshName);

	//attache mesh to scenenode, henceforward we will use mSceneNode to control shape.
    mSceneNode->attachObject(mEntity);

	//for scale, won't be needed in future hopefully...
	Vector3D v;
	v.x = mScale;
	v.y = mScale;
	v.z = mScale;
	scale(v);
}

void ShapeOgre::setupTitle()
{
	/*********  setup title/billboard ***************/
	const Ogre::String& titlename = "tn" + StringConverter::toString(mIndex);
	const Ogre::String& title = "ti" + StringConverter::toString(mIndex);
	const Ogre::String& fontName = "SdkTrays/Caption";
	const Ogre::ColourValue& color = Ogre::ColourValue::White;
	mObjectTitle = new ObjectTitle
	(titlename, mEntity, mGameOgre->mApplicationOgre->getSceneManager()->getCamera("PlayerCam"), title,
    fontName, color);
}

void ShapeOgre::scale(Vector3D scaleVector)
{
	getSceneNode()->scale(scaleVector.x, scaleVector.y, scaleVector.z);
}

void ShapeOgre::checkExtents(Vector3D min)
{

	Ogre::Vector3 max;
	max = Ogre::Vector3::UNIT_SCALE;

	assert( (min.x <= max.x && min.y <= max.y && min.z <= max.z) &&
                "you have a problem with a vector maybe dividing by zero or a garbage value!" );

			//mExtent = EXTENT_FINITE;
			//mMinimum = min;
			//mMaximum = max;
}
void ShapeOgre::setRotation(Vector3D* vector3D)
{
	Vector3 vec;
	vec.x = vector3D->x;
	vec.y = vector3D->y;
	vec.z = vector3D->z;
	getSceneNode()->setDirection(vec,Ogre::Node::TS_WORLD);
}

Vector3D* ShapeOgre::getRotation()
{
	Vector3D* vector3D = new Vector3D();
	
	vector3D->x = getSceneNode()->_getDerivedOrientation().zAxis().x * -1;
	vector3D->y = 0.0;
	vector3D->z = getSceneNode()->_getDerivedOrientation().zAxis().z * -1;

	return vector3D;
}

void ShapeOgre::yaw(float amountToYaw, bool convertToDegree)
{
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
float ShapeOgre::getDegreesToSomething(Vector3D* vectorOfSomething)
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

void ShapeOgre::translate(Vector3D* translateVector, int perspective)
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

void ShapeOgre::setPosition(Vector3D* position)
{
	getSceneNode()->setPosition(converToVector3(position));
}

void ShapeOgre::setPosition(float x, float y, float z)
{
	getSceneNode()->setPosition(x,y,z);
}

Vector3D* ShapeOgre::getPosition()
{
	Vector3D* position = new Vector3D();
	position->x = getSceneNode()->getPosition().x;
	position->y = getSceneNode()->getPosition().y;
	position->z = getSceneNode()->getPosition().z;
	return position;
}

Ogre::Vector3 ShapeOgre::converToVector3(Vector3D* vector3d)
{
	Ogre::Vector3 vec3;
	vec3.x = vector3d->x;
	vec3.y = vector3d->y;
	vec3.z = vector3d->z;
	return vec3;
}

void ShapeOgre::setVisible(bool visible)
{
	getSceneNode()->setVisible(visible);
}

//title

void ShapeOgre::drawTitle()
{
	mObjectTitle->setTitle(mObjectTitleString); 
	mObjectTitle->update();
}
void ShapeOgre::appendToTitle(std::string appendage)
{
	mObjectTitleString.append(appendage);
}

void ShapeOgre::appendToTitle(int appendage)
{
	mObjectTitleString.append(StringConverter::toString(appendage));
}

void ShapeOgre::clearTitle()
{
	mObjectTitleString.clear();
}

Quaternion* ShapeOgre::getRotationTo(Vector3D* source, Vector3D* dest)
{
	Quaternion* quaternion = new Quaternion();

	Vector3D* fallbackAxis = new Vector3D(0.0f,0.0f,0.0f);

	Vector3D* v0 = new Vector3D();
	Vector3D* v1 = new Vector3D();
	v0->copyValuesFrom(source);
	v1->copyValuesFrom(dest);

	v0->normalise();	
	v1->normalise();

	float d = v0->dot(v1);

    // If dot == 1, vectors are the same
    if (d >= 1.0f)
    {
		//LogString("VECTORS ARE THE SAME!!!!!!!!!!!!!!!!");
		Quaternion* quaternionIdentity = new Quaternion(1.0,0.0,0.0,0.0);
		return quaternionIdentity;
    }
			
	if (d < (1e-6f - 1.0f))
	{
		LogString("Fallback");
		// rotate 180 degrees about the fallback axis
		Vector3 fb;
		fb.x = fallbackAxis->x;
		fb.y = fallbackAxis->y;
		fb.z = fallbackAxis->z;
		//quaternion->FromAngleAxis(Radian(Math::PI), fb);
		
		// rotate 180 degrees about the fallback axis
		quaternion->FromAngleAxis(Radian(Math::PI), fb);
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