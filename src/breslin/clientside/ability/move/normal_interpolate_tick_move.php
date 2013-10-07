var NormalInterpolateTickMove = new Class(
{

Extends: AbilityMoveState,
initialize: function (move)
{
	this.mMove = move;
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
 	//this.mAbilityMove.mShape.mObjectTitle.innerHTML='' + ername + ':' + this.mIndex;
 	//this.mAbilityMove.mShape.mObjectTitle.innerHTML='N';  
},

execute: function()
{
        //to be used to setPosition
        transVector = new Vector3D();


        //copy values from mVelocity so we don't make changes to original
        transVector.copyValuesFrom(this.mMove.mShape.mCommandToRunOnShape.mVelocity);
        //get the mulitplier
        parsedRenderTime = parseFloat(this.mMove.mShape.mApplication.getRenderTime());
	
	multipliedRenderTime = parsedRenderTime * 1000;

        //multiply our vector using render values
        transVector.multiply(multipliedRenderTime);

	transVector.add(this.mMove.mShape.getPosition());

	//add our velocity to current position

	//set new position
	this.mMove.mShape.setPosition(transVector);
	//document.getElementById('mMessageFrameG').innerHTML=':mSequence ' + this.mMove.mShape.mApplication.mGame.mSequence;	
/*
        if (abilityMove->mShape->mLocal == 1)
        {
                abilityMove->mShape->mApplication->getCamera()->setPosition(Ogre::Vector3(transVector->x,transVector->y + 20,transVector->z + 20));
                abilityMove->mShape->mApplication->getCamera()->lookAt(Ogre::Vector3(transVector->x,transVector->y,transVector->z));

        }

*/
},

exit: function()
{

}


});

