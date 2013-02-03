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
	//transVector.printValues();
	//good to here
	
        //get the mulitplier
        parsedRenderTime = parseFloat(this.mAbilityMove.mShape.mApplicationBreslin.getRenderTime());
	multipliedRenderTime = parsedRenderTime * 1000;
	//this.log('m:' + multipliedRenderTime);
	//multipliedRenderTime is nice.

        //multiply our vector using render values
	
        transVector.multiply(multipliedRenderTime);
	//transVector.printValues();
	//good thru here

/*
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
*/
	this.mAbilityMove.mShape.getPosition().printValues();
	transVector.add(this.mAbilityMove.mShape.getPosition());
	//add our velocity to current position

	//transVector.printValues();

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

