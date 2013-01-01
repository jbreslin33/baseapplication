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

        //mesh
        mMeshCode    = m;

        //figure out mesh based on code passed in byteBuffer
        //mMeshName = getMeshString(mMeshCode);

        //animate
        mAnimate = m;

        //should I set the commands mServerCommandLast and mServerCommandCurrent here?
        this.mServerCommandLast.mPosition.copyValuesFrom(this.mSpawnPosition);
        this.mServerCommandCurrent.mPosition.copyValuesFrom(this.mSpawnPosition);

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

},

setupTitle: function()
{

},

setVisible: function(b)
{

}



});

