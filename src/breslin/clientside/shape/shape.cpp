//header
#include "shape.h"

//log
#include "../tdreamsock/dreamSockLog.h"

//applicationBreslin
#include "../application/applicationBreslin.h"

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

//move
#include "../move/move.h"

Shape::Shape(ApplicationBreslin* application, ByteBuffer* byteBuffer, bool isGhost)
{

	mMove = NULL;

	mIsGhost = isGhost;

	//applicationBreslin
	mApplication = application;

	//commands
	mServerCommandLast    = new Command();
	mServerCommandCurrent = new Command();
	mCommandToRunOnShape  = new Command();
	//speed
	mSpeed = 0.0f;
	mSpeedMax  = 1.66f;

	mVelocity = new Vector3D();

	//spawn orientation
	mSpawnPosition     = new Vector3D();
	mSpawnRotation     = new Vector3D();

	//process Spawn ByteBuffer
	processSpawnByteBuffer(byteBuffer);

	//animation
	if (mAnimate)
	{
		addAbility(new AbilityAnimationOgre(this));
	}
	
	//title
	mObjectTitle = NULL;

	//ghost
	mGhost = NULL;

	if (!mIsGhost) 
	{
		setupTitle();

		//create a ghost for this shape
		mGhost = new Shape(mApplication,byteBuffer,true);
		mGhost->setVisible(false);
	}

}
Shape::~Shape()
{
	LogString("Destructor for Shape:%d",mIndex);
	//delete mEntity;
//	delete mObjectTitle;
//	delete mSceneNode;
	delete mServerCommandLast;
	delete mServerCommandCurrent;
	delete mCommandToRunOnShape;
}

void Shape::setText(ByteBuffer* byteBuffer)
{
	mText.clear();

        //text
        int length = byteBuffer->ReadByte();
        for (int i = 0; i < length; i++)
        {
                char c =  byteBuffer->ReadByte();
                mText.append(1,c);
        }
}


/*********************************
		ABILITY
******************************/

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
/*********************************
		SPAWN
******************************/

void Shape::processSpawnByteBuffer(ByteBuffer* byteBuffer)
{
	parseSpawnByteBuffer(byteBuffer);
	spawnShape(mSpawnPosition);
}

void Shape::parseSpawnByteBuffer(ByteBuffer* byteBuffer)
{
	byteBuffer->BeginReading();

	byteBuffer->ReadByte(); //should read -103 to add a shape..


	mLocal	=    byteBuffer->ReadByte();
	mIndex	=    byteBuffer->ReadByte();

	mSpawnPosition->x =   byteBuffer->ReadFloat();
	mSpawnPosition->y =   byteBuffer->ReadFloat();
	mSpawnPosition->z =   byteBuffer->ReadFloat();
	
	mSpawnRotation->x = byteBuffer->ReadFloat();
	mSpawnRotation->z = byteBuffer->ReadFloat();
	
	//mesh
	mMeshCode    = byteBuffer->ReadByte();
	
	//figure out mesh based on code passed in byteBuffer
	mMeshName = getMeshString(mMeshCode);

	//animate
	mAnimate = byteBuffer->ReadByte();

	//username
        int length = byteBuffer->ReadByte();
       	for (int i = 0; i < length; i++)
        {
        	char c =  byteBuffer->ReadByte();
                mStringUsername.append(1,c);
        }

	//setText
	mText.clear();
	mText.append(mStringUsername);

	//should I set the commands mServerCommandLast and mServerCommandCurrent here?
	mServerCommandLast->mPosition->copyValuesFrom(mSpawnPosition);
	mServerCommandCurrent->mPosition->copyValuesFrom(mSpawnPosition);


	

}

void Shape::spawnShape(Vector3D* position)
{
	/*********  create shape ***************/
	if (mIsGhost)
	{
		mIndex = mIndex * -1;
	}	

	mName         = StringConverter::toString(mIndex);
	mSceneNode    = mApplication->getSceneManager()->getRootSceneNode()->createChildSceneNode();

	//set Starting position of sceneNode, we will attach our mesh to this. this is all that's needed for static shapes. actually we need to add
	//rotation for them
	mSceneNode->setPosition(position->x,position->y,position->z);	
	
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

/*********************************
		DELTA
******************************/

void Shape::processDeltaByteBuffer(ByteBuffer* byteBuffer)
{
	clearTitle(); //empty title string so it can be filled anew
/*	
	std::string s;

	s.append(mStringUsername);
	s.append(":");
	s.append(StringConverter::toString(mIndex));
 
	appendToTitle(s);
*/
	clearTitle();
	appendToTitle(mText);
	

	parseDeltaByteBuffer(byteBuffer);

	//process ticks on abilitys
	for (unsigned int i = 0; i < mAbilityVector.size(); i++)
	{
		mAbilityVector.at(i)->processTick();
	}
	mMove->processTick();

	//run billboard here for now.
	if (!mIsGhost)
	{
		drawTitle();
	}
}

int Shape::parseDeltaByteBuffer(ByteBuffer *mes)
{
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

        //frame time
       // if (flags & mApplication->mGame->mCommandFrameTime)
        //{
                mServerCommandCurrent->mFrameTime = mApplication->mGame->mFrameTimeServer;
                mCommandToRunOnShape->mFrameTime = mServerCommandCurrent->mFrameTime;
       // }

	
       	//LogString("x:%f",mServerCommandCurrent->mPosition->x);         
       	//LogString("z:%f",mServerCommandCurrent->mPosition->z);         

        if (mServerCommandCurrent->mFrameTime != 0) 
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
	
	mCommandToRunOnShape->mVelocity->copyValuesFrom(mServerCommandCurrent->mVelocity);

       //	LogString("x:%f",mServerCommandCurrent->mVelocity->x);         
       	//LogString("z:%f",mServerCommandCurrent->mVelocity->z);         

        return flags;
}

void Shape::interpolateTick(float renderTime)
{
	//interpolate ticks on abilitys
	for (unsigned int i = 0; i < mAbilityVector.size(); i++)
	{
		mAbilityVector.at(i)->interpolateTick(renderTime);
	}
	mMove->interpolateTick(renderTime);
}

void Shape::moveGhostShape()
{
	Vector3D transVector;

	transVector.x = mServerCommandCurrent->mPosition->x;
	transVector.y = 0;
	transVector.z = mServerCommandCurrent->mPosition->z;

	if (mGhost)
	{
		mGhost->setPosition(transVector);
	}
}
/********************************************************
*
*		OGRE_SPECIFIC PRIVATE
*
*********************************************************/

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
	vector3D->convertFromVector3(getSceneNode()->getOrientation().zAxis());
	
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



void Shape::translate(Vector3D* translateVector, int perspective)
{
	if (perspective == 1)
	{
		getSceneNode()->translate(translateVector->convertToVector3(), Ogre::Node::TS_WORLD);
	}
	if (perspective == 2)
	{
		getSceneNode()->translate(translateVector->convertToVector3(), Ogre::Node::TS_LOCAL);
	}
}

void Shape::setPosition(Vector3D position)
{
	getSceneNode()->setPosition(position.convertToVector3());
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

void Shape::setTitle(std::string title)
{
	mObjectTitleString.clear();
	mObjectTitleString.append(title);
}

void Shape::clearTitle()
{
	mObjectTitleString.clear();
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
		mScale = 0.10f;
		return "cube.mesh";
	}
}
