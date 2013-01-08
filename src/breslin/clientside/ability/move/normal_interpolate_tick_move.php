var NormalInterpolateTickMove = new Class(
{

Extends: AbilityMoveState,
initialize: function (abilityMove)
{
	this.mAbilityMove = abilityMove;
},

log: function(msg)
{
        setTimeout(function()
        {
                throw new Error(msg);
        }, 0);
},

enter: function()
{

},

execute: function()
{
        //to be used to setPosition
        transVector = new Vector3D();

        //copy values from mVelocity so we don't make changes to original
        transVector.copyValuesFrom(this.mAbilityMove.mShape.mCommandToRunOnShape.mVelocity);
//	crap value here	       
//	this.log('x:' + this.mAbilityMove.mShape.mCommandToRunOnShape.mVelocity.x);
 //       this.log('z:' + this.mAbilityMove.mShape.mCommandToRunOnShape.mVelocity.z);
        
        
	
        //get the mulitplier
        multipliedRenderTime = this.mAbilityMove.mShape.mApplicationBreslin.getRenderTime() * 1000;
	//this.log('r:' + multipliedRenderTime);
	this.log('r:' + this.mAbilityMove.mShape.mApplicationBreslin.getRenderTime());


        //multiply our vector using render values
        transVector.multiply(multipliedRenderTime);
//	this.log('x:' + transVector.x);
//	this.log('z:' + transVector.z);
        //add our velocity to current position
        transVector.add(this.mAbilityMove.mShape.getPosition());

	//set new position
//ALERT THIS IS GARBAGE VALUE        this.mAbilityMove.mShape.setPosition(transVector);

/*
        if (abilityMove->mShape->mLocal == 1)
        {
                abilityMove->mShape->mApplicationBreslin->getCamera()->setPosition(Ogre::Vector3(transVector->x,transVector->y + 20,transVector->z + 20));
                abilityMove->mShape->mApplicationBreslin->getCamera()->lookAt(Ogre::Vector3(transVector->x,transVector->y,transVector->z));

        }

*/
},

exit: function()
{

}


});

