var Shape = new Class(
{

//Shape(ApplicationBreslin* applicationBreslin, ByteBuffer* byteBuffer, bool isGhost);
//this.mApplicationBreslin,false,index,client,x,z,rx,rz,m,a)
initialize: function(applicationBreslin, isGhost,index,client,x,z,rx,rz,m,a)
{
	this.log('createShape');

	//let's deal with mIndex first and animate as it appears this is done later
	this.mIndex = index;	
	this.mAnimate = a;

	this.mIsGhost = isGhost;

	//abilitys
	this.mAbilityVector = new Array();
        
	//applicationBreslin
        this.mApplicationBreslin = applicationBreslin;

        //commands
        this.mServerCommandLast    = new Command();
        this.mServerCommandCurrent = new Command();
        this.mCommandToRunOnShape  = new Command();
        
        //speed
        this.mSpeed = 0.0;
        this.mSpeedMax  = 1.66;

        this.mVelocity = new Vector3D();

        //spawn orientation
        this.mSpawnPosition     = new Vector3D();
        this.mSpawnRotation     = new Vector3D();

        //process Spawn ByteBuffer
//        this.processSpawnByteBuffer(byteBuffer);
 	this.mLocal  =    client;

        this.mSpawnPosition.x = x;
        this.mSpawnPosition.z = z;

        this.mSpawnRotation.x = rx;
        this.mSpawnRotation.z = rz;

        //should I set the commands mServerCommandLast and mServerCommandCurrent here?
        this.mServerCommandLast.mPosition.copyValuesFrom(this.mSpawnPosition);
        this.mServerCommandCurrent.mPosition.copyValuesFrom(this.mSpawnPosition);
	
	//div
	this.mDiv = new Div(this);

        //mesh
        this.mSrc = this.mMeshName;
	this.mMesh = 0;
        this.mMeshCode    = m;

        //figure out mesh based on code passed in byteBuffer
        this.mMeshName = this.getMeshString(this.mMeshCode);

        //animate
        mAnimate = m;


        //background
        //this.mBackgroundColor = "yellow"; 
        this.mBackgroundColor="#f3f3f3"; 

	//spawn shape
	this.spawnShape(this.mSpawnPosition);	

        //animation
        if (this.mAnimate)
        {
          //      addAbility(new AbilityAnimationOgre(this));
        }

        this.setupTitle();

        //ghost
        this.mGhost = 0;

        if (!this.mIsGhost)
        {
                //create a ghost for this shape
		byteBuffer = new ByteBuffer();
		this.mGhost = new Shape(this.mApplicationBreslin,true,index,client,x,z,rx,rz,m,a)
                this.mGhost.setVisible(false);
        }
},

log: function(msg)
{
	setTimeout(function()
        {
        	throw new Error(msg);
        }, 0);
},

/*
void Shape::interpolateTick(float renderTime)
{

        //interpolate ticks on abilitys
        for (unsigned int i = 0; i < mAbilityVector.size(); i++)
        {
                mAbilityVector.at(i)->interpolateTick(renderTime);
        }
}
*/

interpolateTick: function(renderTime)
{
	//interpolate ticks on abilitys
        for (i = 0; i < this.mAbilityVector.length; i++)
        {
                this.mAbilityVector[i].interpolateTick(renderTime);
        }

},
/*********************************
               ABILITY 
******************************/
addAbility: function(ability)
{
	this.mAbilityVector.push(ability);
},


/*********************************
                SPAWN
******************************/

processSpawnByteBuffer: function(byteBuffer)
{
        this.parseSpawnByteBuffer(byteBuffer);
        //this.spawnShape(mSpawnPosition);
},

/*
void Shape::parseSpawnByteBuffer(ByteBuffer* byteBuffer)
{
        byteBuffer->BeginReading();

        byteBuffer->ReadByte(); //should read -103 to add a shape..


        mLocal  =    byteBuffer->ReadByte();
        mIndex  =    byteBuffer->ReadByte();

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

        //should I set the commands mServerCommandLast and mServerCommandCurrent here?
        mServerCommandLast->mPosition->copyValuesFrom(mSpawnPosition);
        mServerCommandCurrent->mPosition->copyValuesFrom(mSpawnPosition);
}
*/
parseSpawnByteBuffer: function(byteBuffer)
{

},

/*
void Shape::spawnShape(Vector3D* position)
{
*/
        /*********  create shape ***************/
/* 
       if (mIsGhost)
        {
                mIndex = mIndex * -1;
        }

        mName         = StringConverter::toString(mIndex);
        mSceneNode    = mApplicationBreslin->getSceneManager()->getRootSceneNode()->createChildSceneNode();

        //set Starting position of sceneNode, we will attach our mesh to this. this is all that's needed for static shapes. actually we need to add
        //rotation for them
        mSceneNode->setPosition(position->x,position->y,position->z);

        //create mesh
        mEntity = mApplicationBreslin->getSceneManager()->createEntity(mName, mMeshName);

        //attache mesh to scenenode, henceforward we will use mSceneNode to control shape.
        mSceneNode->attachObject(mEntity);

        //for scale, won't be needed in future hopefully...
        Vector3D v;
        v.x = mScale;
        v.y = mScale;
        v.z = mScale;
        scale(v);
}
*/

spawnShape: function(position)
{
	//create the movable div that will be used to move image around.
        this.mDiv = new Div(this);

	this.mSrc = this.mMeshName;

        //create clientImage
        if (this.mSrc)
        {
        	//image to attach to our div "vessel"
                this.mMesh  = document.createElement("IMG");
                this.mMesh.src  = this.mSrc;
                //this.mMesh.style.width = this.mWidth+'px';
                //this.mMesh.style.height = this.mHeight+'px';
        }
        //back to div
        this.mDiv.mDiv.appendChild(this.mMesh);
	
	this.scale();

},
/*********************************
                DELTA
******************************/
/*
void Shape::processDeltaByteBuffer(ByteBuffer* byteBuffer)
{
        clearTitle(); //empty title string so it can be filled anew

        parseDeltaByteBuffer(byteBuffer);

        //process ticks on abilitys
        for (unsigned int i = 0; i < mAbilityVector.size(); i++)
        {
                mAbilityVector.at(i)->processTick();
        }

        //run billboard here for now.
        drawTitle();
}
*/

processDeltaByteBuffer: function(shapesTable)
{
 	this.parseDeltaByteBuffer(shapesTable);
        //process ticks on abilitys
       // for (i = 0; i < this.mAbilityVector.length; i++)
        //{
        	this.mAbilityVector[0].processTick();
        //}       
	//run billboard here for now.
        //drawTitle();
},

parseDeltaByteBuffer: function(shapesTable)
{
	byteBuffer.beginReading();

	moveXChanged = true;
	moveZChanged = true;
                                
	//x
       	this.mServerCommandLast.mPosition.x = this.mServerCommandCurrent.mPosition.x;
       	this.mServerCommandCurrent.mPosition.x = shapesTable.rows.item(i).cells.item(1).innerHTML; 
        this.mServerCommandCurrent.mVelocity.x = this.mServerCommandCurrent.mPosition.x - this.mServerCommandLast.mPosition.x;
	
	//z
       	this.mServerCommandLast.mPosition.z = this.mServerCommandCurrent.mPosition.z;
       	this.mServerCommandCurrent.mPosition.z = shapesTable.rows.item(i).cells.item(2).innerHTML; 
        this.mServerCommandCurrent.mVelocity.z = this.mServerCommandCurrent.mPosition.z - this.mServerCommandLast.mPosition.z;

	this.log('x:' + this.mServerCommandCurrent.mPosition.x)
	this.log('z:' + this.mServerCommandCurrent.mPosition.z)

        this.mCommandToRunOnShape.mVelocity.copyValuesFrom(this.mServerCommandCurrent.mVelocity);
},
/*
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
       // if (flags & mApplicationBreslin->mGame->mCommandFrameTime)
        //{
                mServerCommandCurrent->mFrameTime = mApplicationBreslin->mGame->mFrameTimeServer;
                mCommandToRunOnShape->mFrameTime = mServerCommandCurrent->mFrameTime;
       // }

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

        return flags;
}

*/


getMeshString: function(meshCode)
{
        if (meshCode == 0)
        {
                //this cube is exactly 1 ogre world unit. Which I take to be 1 meter.
                this.mScale = .01;
		return "/breslin/vclient/dist/media/materials/textures/red_monster.png";
        }
        if (meshCode == 1)
        {
                this.mScale = 1;
		return "/breslin/vclient/dist/media/materials/textures/wizard.png";
        }
},

scale: function()
{
	var h = this.mMesh.height;
	var w = this.mMesh.width;

	h = h * this.mScale;
	w = w * this.mScale;
	
	//scale image 
        this.mMesh.style.width = w+'px';
        this.mMesh.style.height = h+'px';

	//scale div
        this.mDiv.mDiv.style.width = w+'px';
        this.mDiv.mDiv.style.height = h+'px';
	//this.log('h:' + this.mDiv.mDiv.height);
},

setupTitle: function()
{

},

setVisible: function(b)
{

},
/*
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
*/
moveGhostShape: function()
{
/*
	transVector = new Vector3D();

	transVector.x = mServerCommandCurrent.mPosition.x;
	transVector.y = 0;
	transVector.x = mServerCommandCurrent.mPosition.z;
		
	mGhost.setPosition(transVector);
*/
}


});

