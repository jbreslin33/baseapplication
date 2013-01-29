var Shape = new Class(
{

//Shape(ApplicationBreslin* applicationBreslin, ByteBuffer* byteBuffer, bool isGhost);
//this.mApplicationBreslin,false,index,client,x,z,rx,rz,m,a)
initialize: function(applicationBreslin, byteBuffer, isGhost)
{
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
	byteBuffer.beginReading();
	this.log('b:' + byteBuffer.readByte());
	this.mLocal           = byteBuffer.readByte();
	this.mIndex           = byteBuffer.readByte();
	this.mSpawnPosition.x = byteBuffer.readByte();
	this.mSpawnPosition.y = byteBuffer.readByte();
	this.mSpawnPosition.z = byteBuffer.readByte();
	this.mSpawnRotation.x = byteBuffer.readByte();
	this.mSpawnRotation.z = byteBuffer.readByte();
	this.mMeshName        = byteBuffer.readByte();
	this.mAnimate         = byteBuffer.readByte();
       
this.log('l:' + this.mLocal);
 
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
		document.getElementById('mMessageFrame').innerHTML='flags:' + flags;	
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
	this.mServerCommandCurrent.mVelocity.printValues();
	
	return flags;
},

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

	//var pos = 'x:' + transVector.x + 'z:' + transVector.z;
	//document.getElementById('mMessageFrame').innerHTML=pos;	
	this.mGhost.setPosition(transVector);
}


});

