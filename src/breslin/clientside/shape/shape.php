var Shape = new Class(
{

//Shape(ApplicationBreslin* applicationBreslin, ByteBuffer* byteBuffer, bool isGhost);

initialize: function(applicationBreslin, byteBuffer, isGhost)
{
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

	//let's deal with mIndex first
	this.mIndex = 0;	

	this.mIsGhost = isGhost;
        
	//applicationBreslin
        this.mApplicationBreslin = applicationBreslin;


	

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

}


});

