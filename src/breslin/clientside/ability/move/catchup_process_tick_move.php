var CatchupProcessTickMove = new Class(
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
//	this.log('enter c');
//	this.mAbilityMove.mShape.mObjectTitle.innerHTML='C';  
},

execute: function()
{
//let's check if it's mInterpLimitHigh is greater than  1 than snap to it.
	if (this.mAbilityMove.mDeltaPosition > 1)
	{
		this.mAbilityMove.mShape.setPosition(this.mAbilityMove.mShape.mServerCommandCurrent.mPosition);
		return;
	}		

        //this.mAbilityMove.mShape.mMesh.innerHTML='C:' + this.mAbilityMove.mShape.mIndex;
	//if we are back in sync
        if(this.mAbilityMove.mDeltaPosition <= this.mAbilityMove.mPosInterpLimitHigh || this.mAbilityMove.mShape.mServerCommandCurrent.mVelocity.isZero())
        {
                this.mAbilityMove.mProcessTickStateMachine.changeState(this.mAbilityMove.mNormalProcessTickMove);
        }
	this.mAbilityMove.mShape.mObjectTitle.innerHTML='C_D:' + this.mAbilityMove.mDeltaPosition;  
        //this is what we will set mCommandToRunOnShape->mVelocity to
        newVelocity = new Vector3D(); //vector to future server pos

        //first set newVelocity to most recent velocity from server.
        newVelocity.copyValuesFrom(this.mAbilityMove.mShape.mServerCommandCurrent.mVelocity);

        //normalise it now we know what direction to head in.
        newVelocity.normalise();

        //le'ts find out how fast
        //change in position times our interp factor
        multiplier = this.mAbilityMove.mDeltaPosition * this.mAbilityMove.mPosInterpFactor;

        //multiply our normalized velocity by multiplier(change * interpfactor)
        newVelocity.multiply(multiplier);

        //add the latest server position to our newvelocity
        newVelocity.add(this.mAbilityMove.mShape.mServerCommandCurrent.mPosition);

        //now subtract our current position from our new velocity
        newVelocity.subtract(this.mAbilityMove.mShape.getPosition());

        //dist from client pos to future server pos
        predictDist = Math.pow(newVelocity.x, 2) + Math.pow(newVelocity.y, 2) + Math.pow(newVelocity.z, 2);
        predictDist = Math.sqrt(predictDist);

        //server velocity
        if(this.mAbilityMove.mShape.mCommandToRunOnShape.mFrameTime != 0)
        {
                this.mAbilityMove.mShape.mSpeed = abilityMove.calculateSpeed(
this.mAbilityMove.mShape.mServerCommandCurrent.mVelocity,
               this.mAbilityMove.mShape.mCommandToRunOnShape.mFrameTime);
        }

        if(this.mAbilityMove.mShape.mSpeed != 0.0)
        {
                //time needed to get to future server pos
                time = this.mAbilityMove.mDeltaPosition * this.mAbilityMove.mPosInterpFactor/this.mAbilityMove.mShape.mSpeed;

                newVelocity.normalise();  //?????what the hell why i am normalizing this after all that work above?

                //client vel needed to get to future server pos in time
                distTime = predictDist/time;
                newVelocity.multiply(distTime);

                //set newVelocity to mCommandToRunOnShape->mVelocity which is what interpolateTick uses
                this.mAbilityMove.mShape.mCommandToRunOnShape.mVelocity.copyValuesFrom(newVelocity);
        }
        else
        {
                //why would catchup ever need to set velocity to zero, wouldn't we simply leave catchup state??
                this.mAbilityMove.mShape.mCommandToRunOnShape.mVelocity.zero();
        }
},

exit: function()
{

}


});

