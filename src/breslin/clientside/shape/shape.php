var Shape = new Class(
{

//Shape(ApplicationBreslin* applicationBreslin, ByteBuffer* byteBuffer, bool isGhost);
//this.mApplicationBreslin,false,index,client,x,z,rx,rz,m,a)
initialize: function(applicationBreslin, byteBuffer, isGhost)
{

	this.mIndex = 0;
	
	//ghost
        this.mGhost = 0;

	//constants
	this.mCommandOriginX   = 4;
	this.mCommandOriginY   = 8;
	this.mCommandOriginZ   = 16;
	this.mCommandRotationX = 32;
	this.mCommandRotationZ = 64;

 	this.mIsGhost = isGhost;
	this.mAnimate = false;
	this.mName = 0;

	//div
	this.mDiv = 0;

	//position
	this.mPosition       = new Vector3D();
	this.mPositionRender = new Vector3D();
	
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

	this.mMesh = 0;
	this.mScale = 1;

	//animation
	this.mAnimation = 0;        
        if (this.mAnimate)
        {
                //this.addAbility(new AbilityAnimationOgre(this));
        }

        //process Spawn ByteBuffer
        this.processSpawnByteBuffer(byteBuffer);

        this.setupTitle();

        if (!this.mIsGhost)
        {
                //create a ghost for this shape
                this.mGhost = new Shape(this.mApplicationBreslin,byteBuffer,true);
        }
},

log: function(msg)
{
	setTimeout(function()
        {
        	throw new Error(msg);
        }, 0);
},

interpolateTick: function(renderTime)
{
	/********* ANIMATION ******************/

        if (this.mAnimation)
        {
                this.mAnimation.update();
        }

	//interpolate ticks on abilitys
        //for (i = 0; i < this.mAbilityVector.length; i++)
        //{
                this.mAbilityVector[0].interpolateTick(renderTime);
        //}
	
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
	this.mPosition.x = position.x;
	this.mPosition.y = position.y;
	this.mPosition.z = position.z;

        //set a member position because we are going to have to modify the div's position
        modx = position.x+"px"; 
        mody = position.z+"px"; 
        
        this.mDiv.mDiv.style.left = modx;
        this.mDiv.mDiv.style.top = mody;
},

getPosition: function()
{
	return this.mPosition;
},

//relative movement
render: function()
{
	//center image relative to position set it to mPositionRender
	this.mPositionRender.x = this.mPosition.x - (this.mMesh.height / 2);
	this.mPositionRender.y = 0; 
	this.mPositionRender.z = this.mPosition.z - (this.mMesh.width / 2);
	
	//set a member position because we are going to have to modify the div's position
       	modx = position.x+"px"; 
       	mody = position.z+"px"; 
        
        this.mDiv.mDiv.style.left = modx;
        this.mDiv.mDiv.style.top = mody;
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
	byteBuffer.beginReading();
	typenow               = parseInt(byteBuffer.readByte());
	this.mLocal           = parseInt(byteBuffer.readByte());
	this.mIndex           = parseInt(byteBuffer.readByte());
	this.mSpawnPosition.x = parseFloat(byteBuffer.readByte());
	this.mSpawnPosition.y = parseFloat(byteBuffer.readByte());
	this.mSpawnPosition.z = parseFloat(byteBuffer.readByte());
	this.mSpawnPosition.printValues();
	this.mSpawnRotation.x = parseFloat(byteBuffer.readByte());
	this.mSpawnRotation.z = parseFloat(byteBuffer.readByte());
	this.mMeshCode        = parseInt(byteBuffer.readByte());
	this.mAnimate         = parseInt(byteBuffer.readByte());

	//should I set the commands mServerCommandLast and mServerCommandCurrent here?
        this.mServerCommandLast.mPosition.copyValuesFrom(this.mSpawnPosition);
        this.mServerCommandCurrent.mPosition.copyValuesFrom(this.mSpawnPosition);


	//set control object
	if (this.mLocal == 1)
	{
		this.mApplicationBreslin.mGame.mControlObject = this;
	} 
},

spawnShape: function(position)
{
     	if (this.mIsGhost)
        {
                this.mIndex = this.mIndex * -1;
        }
        this.mName         = this.mIndex;
	
	//create the movable div that will be used to move image around. c++ this is the sceneNode
	this.mPosition.copyValuesFrom(this.mSpawnPosition);  
        this.mDiv = new Div(this);

	this.mSrc = this.getMeshString(this.mMeshCode);
	if (this.mSrc == 99)
	{

	}
	if (this.mSrc == 3)	
	{
                this.mMesh = document.createElement("p");
		this.mMesh.innerHTML='' + this.mIndex;
	}
	else 
	{
        	//create clientImage
        	if (this.mSrc)
        	{
        		//image to attach to our div "vessel"
                	this.mMesh  = document.createElement("IMG");
                	this.mMesh.src  = this.mSrc;
        	}
	}
        
	//back to div
        this.mDiv.mDiv.appendChild(this.mMesh);

	v = new Vector3D();	
	this.scale();

},
setSrc: function(src)
{
	this.mSrc = src;
	this.mMesh.src = src;
},
/*********************************
                DELTA
******************************/
processDeltaByteBuffer: function(byteBuffer)
{
 	this.parseDeltaByteBuffer(byteBuffer);
        this.mAbilityVector[0].processTick();
},

parseDeltaByteBuffer: function(byteBuffer)
{
	var flags = 0;

        var moveXChanged = true;
        var moveYChanged = true;
       	var moveZChanged = true;

	flags = byteBuffer.readByte();
	if (this.mIndex == 1)
	{
	
	}

	// Origin
        if(flags & this.mCommandOriginX)
        {
                this.mServerCommandLast.mPosition.x = this.mServerCommandCurrent.mPosition.x;
                this.mServerCommandCurrent.mPosition.x = byteBuffer.readByte();
        }
        else
        {
                moveXChanged = false;
        }

        if(flags & this.mCommandOriginY)
        {
                this.mServerCommandLast.mPosition.y = this.mServerCommandCurrent.mPosition.y;
                this.mServerCommandCurrent.mPosition.y = byteBuffer.readByte();
        }
        else
        {
                moveYChanged = false;
        }

        if(flags & this.mCommandOriginZ)
        {
                this.mServerCommandLast.mPosition.z = this.mServerCommandCurrent.mPosition.z;
                this.mServerCommandCurrent.mPosition.z = byteBuffer.readByte();
        }
        else
        {
                moveZChanged = false;
        }

 	//rotation
        if(flags & this.mCommandRotationX)
        {
                this.mServerCommandLast.mRotation.x = this.mServerCommandCurrent.mRotation.x;
                this.mServerCommandCurrent.mRotation.x = byteBuffer.readByte();
        }

        if(flags & this.mCommandRotationZ)
        {
                this.mServerCommandLast.mRotation.z = this.mServerCommandCurrent.mRotation.z;
                this.mServerCommandCurrent.mRotation.z = byteBuffer.readByte();
        }

        this.mServerCommandCurrent.mFrameTime = this.mApplicationBreslin.mGame.mFrameTimeServer;
        this.mCommandToRunOnShape.mFrameTime = this.mServerCommandCurrent.mFrameTime;

        if (this.mServerCommandCurrent.mFrameTime != 0)
        {
                //position
                if (moveXChanged)
                {
                        this.mServerCommandCurrent.mVelocity.x = this.mServerCommandCurrent.mPosition.x - this.mServerCommandLast.mPosition.x;
               }
                else
                {
                        this.mServerCommandCurrent.mVelocity.x = 0.0;
                }

                if (moveYChanged)
                {
                        this.mServerCommandCurrent.mVelocity.y = this.mServerCommandCurrent.mPosition.y - this.mServerCommandLast.mPosition.y;
                }
                else
                {
                        this.mServerCommandCurrent.mVelocity.y = 0.0;
                }

                if (moveZChanged)
                {
                        this.mServerCommandCurrent.mVelocity.z = this.mServerCommandCurrent.mPosition.z - this.mServerCommandLast.mPosition.z;
                }
                else
                {
                        this.mServerCommandCurrent.mVelocity.z = 0.0;
                }
        }
	this.mCommandToRunOnShape.mVelocity.copyValuesFrom(this.mServerCommandCurrent.mVelocity);
	
	
	return flags;
},

getMeshString: function(meshCode)
{
        if (meshCode == 0)
        {
                //this cube is exactly 1 ogre world unit. Which I take to be 1 meter.
                this.mScale = .01;
        }
        if (meshCode == 1)
        {
                this.mScale = .5;
	
		if (!this.mIsGhost)
		{

 			//set animation instance
                	this.mAnimation = new AnimationAdvanced(this);
                	this.mAnimation.addAnimations('http://' + this.mApplicationBreslin.mNetwork.mServerIP + '/breslin/vclient/dist/media/materials/textures/wizard_','.png');
			return 99;
		}
		else
		{
			return "http://" + this.mApplicationBreslin.mNetwork.mServerIP + "/breslin/vclient/dist/media/materials/textures/red_monster.png";

		}
        }
},

scale: function(v)
{
	var h = this.mMesh.height;
	var w = this.mMesh.width;

	h = h * this.mScale;
	w = w * this.mScale;
	
	//scale image 
       	this.mMesh.style.height = h+'px';
        this.mMesh.style.width = w+'px';

	//scale div
        this.mDiv.mDiv.style.height = h+"px";
        this.mDiv.mDiv.style.width = w+"px";
},

setupTitle: function()
{

},

setVisible: function(b)
{
	if (b)
        {
        	if (this.mDiv.mDiv.style.visibility != 'visible')
        	{
        		this.mDiv.mDiv.style.visibility = 'visible';
        	}
        }
        else
        {
               	if (this.mDiv.mDiv.style.visibility != 'hidden')
                {
			this.log('hiding!!!!!!!!!!!');
                        this.mDiv.mDiv.style.visibility = 'hidden';
               	}
        }
},


moveGhostShape: function()
{
	transVector = new Vector3D();

	transVector.x = this.mServerCommandCurrent.mPosition.x;
	transVector.y = 0;
	transVector.z = this.mServerCommandCurrent.mPosition.z;

	//var pos = 'x:' + transVector.x + 'z:' + transVector.z;
	this.mGhost.setPosition(transVector);
}


});

