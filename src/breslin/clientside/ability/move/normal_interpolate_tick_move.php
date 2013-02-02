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
        //this.log('index:' + this.mAbilityMove.mShape.mIndex);
	//this is only printing out mIndex of last shape created that is the problem...	

        //to be used to setPosition
        transVector = new Vector3D();

        //copy values from mVelocity so we don't make changes to original
        transVector.copyValuesFrom(this.mAbilityMove.mShape.mCommandToRunOnShape.mVelocity);

	
        //get the mulitplier
        multipliedRenderTime = this.mAbilityMove.mShape.mApplicationBreslin.getRenderTime() * 1000;

        //multiply our vector using render values
	
	//transVector.printValues();
        transVector.multiply(multipliedRenderTime);

	position = this.mAbilityMove.mShape.getPosition(); 
	x = position.x; 
	y = 0; 
	z = position.z;	

	x = x.replace("px","");
	z = z.replace("px","");

	actualPosition = new Vector3D();
	actualPosition.x = x; 
	actualPosition.y = 0; 
	actualPosition.z = z; 

	//add our velocity to current position
        transVector.add(actualPosition);

	//set new position
	this.mAbilityMove.mShape.setPosition(transVector);
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

