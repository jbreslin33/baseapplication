//header
#include "shape.h"

//log
#include "../tdreamsock/dreamSockLog.h"

//application
#include "../game/application.h"

//game
#include "../game/game.h"

//command
#include "../command/command.h"

//math
#include "../../math/vector3D.h"

//ability
#include "../ability/animation/abilityAnimationOgre.h"

//byteBuffer
#include "../bytebuffer/byteBuffer.h"

//ObjectTitle
#include "../billboard/objectTitle.h"

Shape::Shape(Application* application, ByteBuffer* byteBuffer, bool isGhost)
{
	//application
	mApplication = application;

	//id
	mIndex = 0;

	//speed
	mSpeed = 0.0f;
	mSpeedMax  = 1.66f;

	//commands
	mServerCommandCurrent = new Command();
	mServerCommandLast    = new Command();
	mCommandToRunOnShape  = new Command();

	//orientation
	mPosition     = new Vector3D();
	mRotation     = new Vector3D();

	//mesh
	mMeshCode = 0;

	//animate
	mAnimate = false;

	//byteBuffer
	parseByteBuffer(byteBuffer);

	//ghost
	mGhost = NULL;

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
		mGhost = new Shape(mApplication,byteBuffer,true);
		mGhost->setVisible(true);
	}

}
Shape::~Shape()
{
}



void Shape::addAbility(Ability* ability)
{
	
	mAbilityVector.push_back(ability);	
}

Ability* Shape::getAbility(Ability* ability)
{
	for (unsigned int i = 0; i < mAbilityVector.size(); i++)
	{
		//typeid(ability);

		if (typeid(ability) == typeid(mAbilityVector.at(i)))
		{
			return mAbilityVector.at(i);
		}
	}
	return 0;
}

void Shape::parseByteBuffer(ByteBuffer* byteBuffer)
{
	byteBuffer->BeginReading();
	byteBuffer->ReadByte(); //should read -103 to add a shape..
	mLocal	=    byteBuffer->ReadByte();
	mIndex		=    byteBuffer->ReadByte();

	mPosition->x =   byteBuffer->ReadFloat();
	mPosition->y =   byteBuffer->ReadFloat();
	mPosition->z =   byteBuffer->ReadFloat();

	mRotation->x = byteBuffer->ReadFloat();
	mRotation->z = byteBuffer->ReadFloat();
	
	//mesh
	mMeshCode    = byteBuffer->ReadByte();

	//animate
	mAnimate = byteBuffer->ReadByte();
}

void Shape::processTick()
{
	clearTitle(); //empty title string so it can be filled anew

	//process ticks on abilitys
	for (unsigned int i = 0; i < mAbilityVector.size(); i++)
	{
		mAbilityVector.at(i)->processTick();
	}

	//run billboard here for now.
	drawTitle();
}
void Shape::interpolateTick(float renderTime)
{
	//interpolate ticks on abilitys
	for (unsigned int i = 0; i < mAbilityVector.size(); i++)
	{
		mAbilityVector.at(i)->interpolateTick(renderTime);
	}
}

//this is all shapes coming to client game from server
//should a shape be responsible to read it's own command?????
//once we determine it's about him shouldn't we pass it off to
//shape object to handle?
void Shape::readDeltaMoveCommand(ByteBuffer *mes)
{
	//Shape* shape = NULL;

	int flags = 0;

	bool moveXChanged = true;
	bool moveYChanged = true;
	bool moveZChanged = true;

	// Flags
	flags = mes->ReadByte();

	// Origin
	if(flags & mCommandOriginX)
	{
		mServerCommandLast->mPosition->x = mServerCommandCurrent->mPosition->x;
		mServerCommandCurrent->mPosition->x = mes->ReadFloat();		
	}
	else
	{
		moveXChanged = false;
	}

	if(flags & mCommandOriginY)
	{
		mServerCommandLast->mPosition->y = mServerCommandCurrent->mPosition->y;
		mServerCommandCurrent->mPosition->y = mes->ReadFloat();
	}
	else
	{
		moveYChanged = false;
	}

	if(flags & mCommandOriginZ)
	{
		mServerCommandLast->mPosition->z = mServerCommandCurrent->mPosition->z;
		mServerCommandCurrent->mPosition->z = mes->ReadFloat();	
	}
	else
	{
		moveZChanged = false;
	}

	//rotation
	if(flags & mCommandRotationX)
	{
		mServerCommandLast->mRotation->x = mServerCommandCurrent->mRotation->x;
		mServerCommandCurrent->mRotation->x = mes->ReadFloat();
	}

	if(flags & mCommandRotationZ)
	{
		mServerCommandLast->mRotation->z = mServerCommandCurrent->mRotation->z;
		mServerCommandCurrent->mRotation->z = mes->ReadFloat();
	}

	//milliseconds
	if (flags & mApplication->mCommandMilliseconds)
	{
		mServerCommandCurrent->mMilliseconds = mes->ReadByte();
		mCommandToRunOnShape->mMilliseconds = mServerCommandCurrent->mMilliseconds;
	}

	if (mServerCommandCurrent->mMilliseconds != 0) 
	{
		//position
		if (moveXChanged)
		{
			mServerCommandCurrent->mVelocity->x = mServerCommandCurrent->mPosition->x - mServerCommandLast->mPosition->x;
		}
		else
		{
			mServerCommandCurrent->mVelocity->x = 0.0;
		}
		
		if (moveYChanged)
		{
			mServerCommandCurrent->mVelocity->y = mServerCommandCurrent->mPosition->y - mServerCommandLast->mPosition->y;
		}
		else
		{
			mServerCommandCurrent->mVelocity->y = 0.0;
		}

		if (moveZChanged)
		{
			mServerCommandCurrent->mVelocity->z = mServerCommandCurrent->mPosition->z - mServerCommandLast->mPosition->z;
		}
		else
		{
			mServerCommandCurrent->mVelocity->z = 0.0;
		}
	}

}


void Shape::moveGhostShape()
{
	Vector3D* transVector = new Vector3D();

	transVector->x = mServerCommandCurrent->mPosition->x;
	transVector->y = 0;
	transVector->z = mServerCommandCurrent->mPosition->z;

	if (mGhost)
	{
		mGhost->setPosition(transVector);
	}
}
/********************************************************
*
*				OGRE_SPECIFIC PRIVATE
*
*********************************************************/


void Shape::createShape()
{
	/*********  create shape ***************/
	mName         = StringConverter::toString(mIndex);
	mSceneNode    = mApplication->getSceneManager()->getRootSceneNode()->createChildSceneNode();

	//set Starting position of sceneNode, we will attach our mesh to this. this is all that's needed for static shapes. actually we need to add
	//rotation for them
	mSceneNode->setPosition(mPosition->x,mPosition->y,mPosition->z);	
	
	//create mesh
	mEntity = mApplication->getSceneManager()->createEntity(mName, mMeshName);

	//attache mesh to scenenode, henceforward we will use mSceneNode to control shape.
    mSceneNode->attachObject(mEntity);

	//for scale, won't be needed in future hopefully...
	Vector3D v;
	v.x = mScale;
	v.y = mScale;
	v.z = mScale;
	scale(v);
}

void Shape::setupTitle()
{
	/*********  setup title/billboard ***************/
	const Ogre::String& titlename = "tn" + StringConverter::toString(mIndex);
	const Ogre::String& title = "ti" + StringConverter::toString(mIndex);
	const Ogre::String& fontName = "SdkTrays/Caption";
	const Ogre::ColourValue& color = Ogre::ColourValue::White;
	mObjectTitle = new ObjectTitle
	(titlename, mEntity, mApplication->getSceneManager()->getCamera("PlayerCam"), title,
    fontName, color);
}

void Shape::scale(Vector3D scaleVector)
{
	getSceneNode()->scale(scaleVector.x, scaleVector.y, scaleVector.z);
}

void Shape::checkExtents(Vector3D min)
{

	Ogre::Vector3 max;
	max = Ogre::Vector3::UNIT_SCALE;

	assert( (min.x <= max.x && min.y <= max.y && min.z <= max.z) &&
                "you have a problem with a vector maybe dividing by zero or a garbage value!" );

			//mExtent = EXTENT_FINITE;
			//mMinimum = min;
			//mMaximum = max;
}
void Shape::setRotation(Vector3D* vector3D)
{
	Vector3 vec;
	vec.x = vector3D->x;
	vec.y = vector3D->y;
	vec.z = vector3D->z;
	getSceneNode()->setDirection(vec,Ogre::Node::TS_WORLD);
}

Vector3D* Shape::getRotation()
{
	Vector3D* vector3D = new Vector3D();
	
	vector3D->x = getSceneNode()->_getDerivedOrientation().zAxis().x * -1;
	vector3D->y = 0.0;
	vector3D->z = getSceneNode()->_getDerivedOrientation().zAxis().z * -1;

	return vector3D;
}

void Shape::yaw(float amountToYaw, bool convertToDegree)
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
float Shape::getDegreesToSomething(Vector3D* vectorOfSomething)
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

void Shape::translate(Vector3D* translateVector, int perspective)
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

void Shape::setPosition(Vector3D* position)
{
	getSceneNode()->setPosition(converToVector3(position));
}

void Shape::setPosition(float x, float y, float z)
{
	getSceneNode()->setPosition(x,y,z);
}

Vector3D* Shape::getPosition()
{
	Vector3D* position = new Vector3D();
	position->x = getSceneNode()->getPosition().x;
	position->y = getSceneNode()->getPosition().y;
	position->z = getSceneNode()->getPosition().z;
	return position;
}

Ogre::Vector3 Shape::converToVector3(Vector3D* vector3d)
{
	Ogre::Vector3 vec3;
	vec3.x = vector3d->x;
	vec3.y = vector3d->y;
	vec3.z = vector3d->z;
	return vec3;
}

void Shape::setVisible(bool visible)
{
	getSceneNode()->setVisible(visible);
}

//title

void Shape::drawTitle()
{
	mObjectTitle->setTitle(mObjectTitleString); 
	mObjectTitle->update();
}
void Shape::appendToTitle(std::string appendage)
{
	mObjectTitleString.append(appendage);
}

void Shape::appendToTitle(int appendage)
{
	mObjectTitleString.append(StringConverter::toString(appendage));
}

void Shape::clearTitle()
{
	mObjectTitleString.clear();
}

Quaternion* Shape::getRotationTo(Vector3D* source, Vector3D* dest)
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

std::string Shape::getMeshString(int meshCode)
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
