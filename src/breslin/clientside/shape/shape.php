var Shape = new Class(
{

//Shape(ApplicationBreslin* applicationBreslin, ByteBuffer* byteBuffer, bool isGhost);

initialize: function(applicationBreslin, byteBuffer, isGhost)
{
	//let's deal with mIndex first and animate as it appears this is done later
	this.mIndex = 0;	
	this.mAnimate = false;

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
        this.processSpawnByteBuffer(byteBuffer);

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


processSpawnByteBuffer: function(byteBuffer)
{

},

setupTitle: function()
{

},

setVisible: function(b)
{

}

});

