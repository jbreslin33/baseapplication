//header
#include "shape.h"

//log
#include "../tdreamsock/dreamSockLog.h"

//parser
#include "../parser/parser.h"


//math
#include "../../math/vector3D.h"

Shape::Shape(ByteBuffer* byteBuffer, bool isGhost)
{
	//id
	mIndex = 0;

	//parser
	mParser = new Parser();

	//commands
	mServerFrame         = new Command();
	mCommandToRunOnShape = new Command();

	//speed
	mSpeed = 0.0f;
	mSpeedMax  = 1.66f;

	//orientation
	mPosition     = new Vector3D();
	mMoveVelocity = new Vector3D();
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
	

	//createShape();
	mShapeOgre = new ShapeOgre(this);
	
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
		mGhost = new Shape(byteBuffer,true);
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
	mMoveVelocity->x = byteBuffer->ReadFloat();
	mMoveVelocity->y = byteBuffer->ReadFloat();
	mMoveVelocity->z = byteBuffer->ReadFloat();
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
	if(flags & mParser->mCommandOriginX)
	{
		mServerFrame->mPositionOld->x = mServerFrame->mPosition->x;
		mServerFrame->mPosition->x = mes->ReadFloat();		
	}
	else
	{
		moveXChanged = false;
	}

	if(flags & mParser->mCommandOriginY)
	{
		mServerFrame->mPositionOld->y = mServerFrame->mPosition->y;
		mServerFrame->mPosition->y = mes->ReadFloat();
	}
	else
	{
		moveYChanged = false;
	}

	if(flags & mParser->mCommandOriginZ)
	{
		mServerFrame->mPositionOld->z = mServerFrame->mPosition->z;
		mServerFrame->mPosition->z = mes->ReadFloat();	
	}
	else
	{
		moveZChanged = false;
	}

	//rotation
	if(flags & mParser->mCommandRotationX)
	{
		mServerFrame->mRotOld->x = mServerFrame->mRot->x;
		mServerFrame->mRot->x = mes->ReadFloat();
	}

	if(flags & mParser->mCommandRotationZ)
	{
		mServerFrame->mRotOld->z = mServerFrame->mRot->z;
		mServerFrame->mRot->z = mes->ReadFloat();
	}

	//milliseconds
	if (flags & mParser->mCommandMilliseconds)
	{
		mServerFrame->mMilliseconds = mes->ReadByte();
		mCommandToRunOnShape->mMilliseconds = mServerFrame->mMilliseconds;
	}

	if (mServerFrame->mMilliseconds != 0) 
	{
		//position
		if (moveXChanged)
		{
			mServerFrame->mMoveVelocity->x = mServerFrame->mPosition->x - mServerFrame->mPositionOld->x;
		}
		else
		{
			mServerFrame->mMoveVelocity->x = 0.0;
		}
		
		if (moveYChanged)
		{
			mServerFrame->mMoveVelocity->y = mServerFrame->mPosition->y - mServerFrame->mPositionOld->y;
		}
		else
		{
			mServerFrame->mMoveVelocity->y = 0.0;
		}

		if (moveZChanged)
		{
			mServerFrame->mMoveVelocity->z = mServerFrame->mPosition->z - mServerFrame->mPositionOld->z;
		}
		else
		{
			mServerFrame->mMoveVelocity->z = 0.0;
		}
	}

}


void Shape::moveGhostShape()
{
	Vector3D* transVector = new Vector3D();

	transVector->x = mServerFrame->mPosition->x;
	transVector->y = 0;
	transVector->z = mServerFrame->mPosition->z;

	if (mGhost)
	{
		mGhost->setPosition(transVector);
	}
}


