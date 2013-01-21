var Shape = new Class(
{

//Shape(ApplicationBreslin* applicationBreslin, ByteBuffer* byteBuffer, bool isGhost);
//this.mApplicationBreslin,false,index,client,x,z,rx,rz,m,a)
initialize: function(applicationBreslin, byteBuffer, isGhost)
{
 	this.mIsGhost = isGhost;
	this.mAnimate = false;
	this.mName = 0;
	
	//div
	this.mDiv = 0;
	this.mPosition = new Vector3D();
	
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
        this.processSpawnByteBuffer(byteBuffer);
        
	//animation
        if (this.mAnimate)
        {
                //this.addAbility(new AbilityAnimationOgre(this));
        }

        this.setupTitle();

        //ghost
        this.mGhost = 0;

        if (!this.mIsGhost)
        {
                //create a ghost for this shape
                this.mGhost = new Shape(this.mApplicationBreslin,byteBuffer,true);
                this.mGhost.setVisible(false);
        }

/*
 	mIsGhost = isGhost;

        //applicationBreslin
        mApplicationBreslin = applicationBreslin;

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

        setupTitle();

        //ghost
        mGhost = NULL;

        if (!mIsGhost)
        {
                //create a ghost for this shape
                mGhost = new Shape(mApplicationBreslin,byteBuffer,true);
                mGhost->setVisible(false);
        }

*/

/*
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

	//position
	this.mPosition = new Vector3D();
        
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
*/
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
               MOVE 
******************************/


/*
Shape::translate(Vector3D* translateVector, int perspective)
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
*/

setPosition: function(position)
{
	//set a member position because we are going to have to modify the div's position
        modx = position.x+"px"; 
        mody = position.z+"px"; 
        
        this.mDiv.mDiv.style.left = modx;
        this.mDiv.mDiv.style.top = mody;
},

/*
Vector3D* Shape::getPosition()
{
        Vector3D* position = new Vector3D();
        position->x = getSceneNode()->getPosition().x;
        position->y = getSceneNode()->getPosition().y;
        position->z = getSceneNode()->getPosition().z;
        return position;
}
*/

getPosition: function()
{
	x = this.mDiv.mDiv.style.left;
	y = 0; 
        z = this.mDiv.mDiv.style.top;

	x = x.replace(/\D/g,'');	
	z = z.replace(/\D/g,'');	
	
	v = new Vector3D(x,y,z);

	return v;
},

setVisible: function(b)
{

},

/*********************************
                SPAWN
******************************/
processSpawnByteBuffer: function(byteBuffer)
{
        this.parseSpawnByteBuffer(byteBuffer);
        this.spawnShape(this.mSpawnPosition);
},

parseSpawnByteBuffer: function(byteBuffer)
{
	this.mLocal           = byteBuffer[1];
	this.mIndex           = byteBuffer[2];
	this.mSpawnPosition.x = byteBuffer[3];
	this.mSpawnPosition.y = byteBuffer[4];
	this.mSpawnPosition.z = byteBuffer[5];
	this.mSpawnRotation.x = byteBuffer[6];
	this.mSpawnRotation.z = byteBuffer[7];
	this.mMeshName        = byteBuffer[8];
	this.mAnimate         = byteBuffer[9];
        
	//should I set the commands mServerCommandLast and mServerCommandCurrent here?
        this.mServerCommandLast.mPosition.copyValuesFrom(this.mSpawnPosition);
        this.mServerCommandCurrent.mPosition.copyValuesFrom(this.mSpawnPosition);
},

spawnShape: function(position)
{
     	if (this.mIsGhost)
        {
                this.mIndex = this.mIndex * -1;
        }
        this.mName         = this.mIndex;
	
	//create the movable div that will be used to move image around. c++ this is the sceneNode
        this.mDiv = new Div(this);

	this.mSrc = this.mMeshName;

        //create clientImage
        if (this.mSrc)
        {
        	//image to attach to our div "vessel"
                this.mMesh  = document.createElement("IMG");
                this.mMesh.src  = this.mSrc;
        }
        //back to div
        this.mDiv.mDiv.appendChild(this.mMesh);

	v = new Vector3D();	
	this.scale(v);
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
processDeltaByteBuffer: function(byteBuffer)
{
 	this.parseDeltaByteBuffer(byteBuffer);
        this.mAbilityVector[0].processTick();
},

parseDeltaByteBuffer: function(byteBuffer)
{
/*
	byteBuffer.beginReading();

	moveXChanged = true;
	moveZChanged = true;
                                
	//x
       	this.mServerCommandLast.mPosition.x = this.mServerCommandCurrent.mPosition.x;
       	this.mServerCommandCurrent.mPosition.x = shapesTable.rows.item(i).cells.item(1).innerHTML; 
        this.mServerCommandCurrent.mVelocity.x = this.mServerCommandCurrent.mPosition.x - this.mServerCommandLast.mPosition.x;
	//this.log('vx:' + this.mServerCommandCurrent.mVelocity.x); 
	
	//z
       	this.mServerCommandLast.mPosition.z = this.mServerCommandCurrent.mPosition.z;
       	this.mServerCommandCurrent.mPosition.z = shapesTable.rows.item(i).cells.item(2).innerHTML; 
        this.mServerCommandCurrent.mVelocity.z = this.mServerCommandCurrent.mPosition.z - this.mServerCommandLast.mPosition.z;
	//this.log('vz:' + this.mServerCommandCurrent.mVelocity.z); 

	//frametime
        this.mServerCommandCurrent.mFrameTime = this.mApplicationBreslin.mGame.mFrameTimeServer;
        this.mCommandToRunOnShape.mFrameTime = this.mServerCommandCurrent.mFrameTime;

        this.mCommandToRunOnShape.mVelocity.copyValuesFrom(this.mServerCommandCurrent.mVelocity);
	//this.log('cvx:' + this.mCommandToRunOnShape.mVelocity.x); 
	//this.log('cvz:' + this.mCommandToRunOnShape.mVelocity.z); 


//	this.log('x:' + this.mServerCommandCurrent.mPosition.x); 	
//	this.log('z:' + this.mServerCommandCurrent.mPosition.z); 	
	//this.log('x:' + this.mServerCommandCurrent.mVelocity.x); 	
	//this.log('z:' + this.mServerCommandCurrent.mVelocity.z); 	
*/
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
        this.mDiv.mDiv.style.width = w+"px";
        this.mDiv.mDiv.style.height = h+"px";
	//this.log('h:' + this.mDiv.mDiv.height);
},

setupTitle: function()
{

},

setVisible: function(b)
{

},

moveGhostShape: function()
{
	transVector = new Vector3D();

	transVector.x = this.mServerCommandCurrent.mPosition.x;
	transVector.y = 0;
	transVector.z = this.mServerCommandCurrent.mPosition.z;
	
	//this.log('x:' + transVector.x);	
	//this.log('z:' + transVector.z);	
	this.mGhost.setPosition(transVector);
}


});

