var NormalProcessTickMove = new Class(
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
//	this.log('enter n');
},

execute: function(move)
{
//	move.mShape.mMesh.innerHTML='n:' + move.mShape.mIndex;

        // if distance exceeds threshold && server velocity is zero
        if(move.mDeltaPosition > move.mPosInterpLimitHigh && !move.mShape.mServerCommandCurrent.mVelocity.isZero())
        {
       		move.mProcessTickStateMachine.changeState(move.mCatchupProcessTickMove);
        }
        
	serverVelocity = new Vector3D();

        serverVelocity.copyValuesFrom(move.mShape.mServerCommandCurrent.mVelocity);
	
        serverVelocity.normalise();

        if(move.mShape.mCommandToRunOnShape.mFrameTime != 0)
        {
                v = move.mShape.mServerCommandCurrent.mVelocity;
                f = move.mShape.mCommandToRunOnShape.mFrameTime;
		
                move.mShape.mSpeed = move.calculateSpeed(v,f);
        }
        serverVelocity.multiply(move.mShape.mSpeed);
 
	move.mShape.mCommandToRunOnShape.mVelocity.copyValuesFrom(serverVelocity);
	
},

exit: function(move)
{

}


});

