var NormalProcessTickMove = new Class(
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
//	this.log('enter n');
},

execute: function()
{
//	this.mMove.mShape.mMesh.innerHTML='n:' + this.mMove.mShape.mIndex;

        // if distance exceeds threshold && server velocity is zero
        if(this.mMove.mDeltaPosition > this.mMove.mPosInterpLimitHigh && !this.mMove.mShape.mServerCommandCurrent.mVelocity.isZero())
        {
       		this.mMove.mProcessTickStateMachine.changeState(this.mMove.mCatchupProcessTickMove);
        }
        
	serverVelocity = new Vector3D();

        serverVelocity.copyValuesFrom(this.mMove.mShape.mServerCommandCurrent.mVelocity);
	
        serverVelocity.normalise();

        if(this.mMove.mShape.mCommandToRunOnShape.mFrameTime != 0)
        {
                v = this.mMove.mShape.mServerCommandCurrent.mVelocity;
                f = this.mMove.mShape.mCommandToRunOnShape.mFrameTime;
		
                this.mMove.mShape.mSpeed = this.mMove.calculateSpeed(v,f);
        }
        serverVelocity.multiply(this.mMove.mShape.mSpeed);
 
	this.mMove.mShape.mCommandToRunOnShape.mVelocity.copyValuesFrom(serverVelocity);
	
},

exit: function()
{

}


});

