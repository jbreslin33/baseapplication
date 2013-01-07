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

/*
void Shape::setPosition(Vector3D* position)
{
        getSceneNode()->setPosition(position->convertToVector3());
}
*/
setPosition: function(position)
{
	//set a member position because we are going to have to modify the div's position
	this.mPosition.x = position.x;
	this.mPosition.z = position.z;

	modx = position.x+'px'; 
	mody = position.z+'px'; 
	//this.log('x:' + modx);
//	this.log('z:' + mody);
       	
//	this.mDiv.mDiv.style.left = modx;
 //     	this.mDiv.mDiv.style.top = mody;
},
/*
setPosition: function(x,z)
{
	//set a member position because we are going to have to modify the div's position
	this.mPosition.x = x;
	this.mPosition.z = z;
	
	modx = x+'px'; 
	mody = z+'px'; 

       	//this.mDiv.mDiv.style.left = modx;
      	//this.mDiv.mDiv.style.top = mody;
},
*/
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
	//just return mPosition for now
	return this.mPosition;
},
/*
void Shape::setVisible(bool visible)
{
        getSceneNode()->setVisible(visible);
}
*/

/*********************************
                SPAWN
******************************/

processSpawnByteBuffer: function(byteBuffer)
{
        this.parseSpawnByteBuffer(byteBuffer);
        //this.spawnShape(mSpawnPosition);
},

parseSpawnByteBuffer: function(byteBuffer)
{

},

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
        }
        //back to div
        this.mDiv.mDiv.appendChild(this.mMesh);
	
	this.scale();

},
/*********************************
                DELTA
******************************/

processDeltaByteBuffer: function(shapesTable)
{
 	this.parseDeltaByteBuffer(shapesTable);
        this.mAbilityVector[0].processTick();
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
	//this.log('vx:' + this.mServerCommandCurrent.mVelocity.x); 
	
	//z
       	this.mServerCommandLast.mPosition.z = this.mServerCommandCurrent.mPosition.z;
       	this.mServerCommandCurrent.mPosition.z = shapesTable.rows.item(i).cells.item(2).innerHTML; 
        this.mServerCommandCurrent.mVelocity.z = this.mServerCommandCurrent.mPosition.z - this.mServerCommandLast.mPosition.z;
	//this.log('vz:' + this.mServerCommandCurrent.mVelocity.z); 

        this.mServerCommandCurrent.mFrameTime = this.mApplicationBreslin.mGame.mFrameTimeServer;
        this.mCommandToRunOnShape.mFrameTime = this.mServerCommandCurrent.mFrameTime;

        this.mCommandToRunOnShape.mVelocity.copyValuesFrom(this.mServerCommandCurrent.mVelocity);
	//this.log('cvx:' + this.mCommandToRunOnShape.mVelocity.x); 
	//this.log('cvz:' + this.mCommandToRunOnShape.mVelocity.z); 
	
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

