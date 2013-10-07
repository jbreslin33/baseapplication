var CatchupProcessTickMove = new Class(
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
},

execute: function()
{
//let's check if it's mInterpLimitHigh is greater than  1 than snap to it.
/*
	if (this.mMove.mDeltaPosition > 1)
	{
		this.mMove.mShape.setPosition(this.mMove.mShape.mServerCommandCurrent.mPosition);
		return;
	}		
*/
        //this.mMove.mShape.mMesh.innerHTML='C:' + this.mMove.mShape.mIndex;
	//if we are back in sync
        if(this.mMove.mDeltaPosition <= this.mMove.mPosInterpLimitHigh || this.mMove.mShape.mServerCommandCurrent.mVelocity.isZero())
        {
                this.mMove.mProcessTickStateMachine.changeState(this.mMove.mNormalProcessTickMove);
        }
	//this.mMove.mShape.mObjectTitle.innerHTML='C_D:' + this.mMove.mDeltaPosition;  
        //this is what we will set mCommandToRunOnShape->mVelocity to
        newVelocity = new Vector3D(); //vector to future server pos

        //first set newVelocity to most recent velocity from server.
        newVelocity.copyValuesFrom(this.mMove.mShape.mServerCommandCurrent.mVelocity);

        //normalise it now we know what direction to head in.
        newVelocity.normalise();

        //le'ts find out how fast
        //change in position times our interp factor
        multiplier = this.mMove.mDeltaPosition * this.mMove.mPosInterpFactor;

        //multiply our normalized velocity by multiplier(change * interpfactor)
        newVelocity.multiply(multiplier);

        //add the latest server position to our newvelocity
        newVelocity.add(this.mMove.mShape.mServerCommandCurrent.mPosition);

        //now subtract our current position from our new velocity
        newVelocity.subtract(this.mMove.mShape.getPosition());

        //dist from client pos to future server pos
        predictDist = Math.pow(newVelocity.x, 2) + Math.pow(newVelocity.y, 2) + Math.pow(newVelocity.z, 2);
        predictDist = Math.sqrt(predictDist);

        //server velocity
        if(this.mMove.mShape.mCommandToRunOnShape.mFrameTime != 0)
        {
                this.mMove.mShape.mSpeed = this.mMove.calculateSpeed(
this.mMove.mShape.mServerCommandCurrent.mVelocity,
               this.mMove.mShape.mCommandToRunOnShape.mFrameTime);
        }

        if(this.mMove.mShape.mSpeed != 0.0)
        {
                //time needed to get to future server pos
                time = this.mMove.mDeltaPosition * this.mMove.mPosInterpFactor/this.mMove.mShape.mSpeed;

                newVelocity.normalise();  //?????what the hell why i am normalizing this after all that work above?

                //client vel needed to get to future server pos in time
                distTime = predictDist/time;
                newVelocity.multiply(distTime);

                //set newVelocity to mCommandToRunOnShape->mVelocity which is what interpolateTick uses
                this.mMove.mShape.mCommandToRunOnShape.mVelocity.copyValuesFrom(newVelocity);
        }
        else
        {
                //why would catchup ever need to set velocity to zero, wouldn't we simply leave catchup state??
                this.mMove.mShape.mCommandToRunOnShape.mVelocity.zero();
        }
},

exit: function()
{

}


});

