var NormalProcessTickMove = new Class(
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
	this.mAbilityMove.mShape.mMesh.innerHTML='n:' + this.mAbilityMove.mShape.mIndex;

        // if distance exceeds threshold && server velocity is zero
        if(this.mAbilityMove.mDeltaPosition > this.mAbilityMove.mPosInterpLimitHigh && !this.mAbilityMove.mShape.mServerCommandCurrent.mVelocity.isZero())
        {
       		//this.mAbilityMove.mProcessTickStateMachine.changeState(this.mAbilityMove.mCatchupProcessTickMove);
        }
        
	serverVelocity = new Vector3D();

        serverVelocity.copyValuesFrom(this.mAbilityMove.mShape.mServerCommandCurrent.mVelocity);
	
        serverVelocity.normalise();

        if(this.mAbilityMove.mShape.mCommandToRunOnShape.mFrameTime != 0)
        {
                v = this.mAbilityMove.mShape.mServerCommandCurrent.mVelocity;
                f = this.mAbilityMove.mShape.mCommandToRunOnShape.mFrameTime;
		
                this.mAbilityMove.mShape.mSpeed = this.mAbilityMove.calculateSpeed(v,f);
        }
        serverVelocity.multiply(this.mAbilityMove.mShape.mSpeed);
 
	this.mAbilityMove.mShape.mCommandToRunOnShape.mVelocity.copyValuesFrom(serverVelocity);
	
},

exit: function()
{

}


});

