var CatchupProcessTickMove = new Class(
{

Extends: State,
initialize: function ()
{
},

log: function(msg)
{
        setTimeout(function()
        {
                throw new Error(msg);
        }, 0);
},

enter: function(move)
{
},

execute: function(move)
{
//let's check if it's mInterpLimitHigh is greater than  1 than snap to it.
/*
	if (move.mDeltaPosition > 1)
	{
		move.mShape.setPosition(move.mShape.mServerCommandCurrent.mPosition);
		return;
	}		
*/
        //move.mShape.mMesh.innerHTML='C:' + move.mShape.mIndex;
	//if we are back in sync
        if(move.mDeltaPosition <= move.mPosInterpLimitHigh || move.mShape.mServerCommandCurrent.mVelocity.isZero())
        {
                move.mProcessTickStateMachine.changeState(move.mNormalProcessTickMove);
        }
	//move.mShape.mObjectTitle.innerHTML='C_D:' + move.mDeltaPosition;  
        //this is what we will set mCommandToRunOnShape->mVelocity to
        newVelocity = new Vector3D(); //vector to future server pos

        //first set newVelocity to most recent velocity from server.
        newVelocity.copyValuesFrom(move.mShape.mServerCommandCurrent.mVelocity);

        //normalise it now we know what direction to head in.
        newVelocity.normalise();

        //le'ts find out how fast
        //change in position times our interp factor
        multiplier = move.mDeltaPosition * move.mPosInterpFactor;

        //multiply our normalized velocity by multiplier(change * interpfactor)
        newVelocity.multiply(multiplier);

        //add the latest server position to our newvelocity
        newVelocity.add(move.mShape.mServerCommandCurrent.mPosition);

        //now subtract our current position from our new velocity
        newVelocity.subtract(move.mShape.getPosition());

        //dist from client pos to future server pos
        predictDist = Math.pow(newVelocity.x, 2) + Math.pow(newVelocity.y, 2) + Math.pow(newVelocity.z, 2);
        predictDist = Math.sqrt(predictDist);

        //server velocity
        if(move.mShape.mCommandToRunOnShape.mFrameTime != 0)
        {
                move.mShape.mSpeed = move.calculateSpeed(
move.mShape.mServerCommandCurrent.mVelocity,
               move.mShape.mCommandToRunOnShape.mFrameTime);
        }

        if(move.mShape.mSpeed != 0.0)
        {
                //time needed to get to future server pos
                time = move.mDeltaPosition * move.mPosInterpFactor/move.mShape.mSpeed;

                newVelocity.normalise();  //?????what the hell why i am normalizing this after all that work above?

                //client vel needed to get to future server pos in time
                distTime = predictDist/time;
                newVelocity.multiply(distTime);

                //set newVelocity to mCommandToRunOnShape->mVelocity which is what interpolateTick uses
                move.mShape.mCommandToRunOnShape.mVelocity.copyValuesFrom(newVelocity);
        }
        else
        {
                //why would catchup ever need to set velocity to zero, wouldn't we simply leave catchup state??
                move.mShape.mCommandToRunOnShape.mVelocity.zero();
        }
},

exit: function(move)
{

}


});

