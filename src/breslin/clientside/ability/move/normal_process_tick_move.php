var NormalProcessTickMove = new Class(
{

Extends: AbilityMoveState,
initialize: function (abilityMove)
{
	this.mAbilityMove = abilityMove;
},

enter: function()
{

},

execute: function()
{
/*
        //abilityMove->mShape->appendToTitle("M:Normal");

        // if distance exceeds threshold && server velocity is zero
        if(abilityMove->mDeltaPosition > abilityMove->mPosInterpLimitHigh && !abilityMove->mShape->mServerCommandCurrent->mVelocity->isZero())
        {
                abilityMove->mProcessTickStateMachine->changeState(Catchup_ProcessTick_Move::Instance());
        }

        Vector3D* serverVelocity = new Vector3D();
        serverVelocity->copyValuesFrom(abilityMove->mShape->mServerCommandCurrent->mVelocity);
        serverVelocity->normalise();

        if(abilityMove->mShape->mCommandToRunOnShape->mFrameTime != 0)
        {
                abilityMove->mShape->mSpeed = abilityMove->calcuateSpeed(
                abilityMove->mShape->mServerCommandCurrent->mVelocity,
                abilityMove->mShape->mCommandToRunOnShape->mFrameTime);
        }

        serverVelocity->multiply(abilityMove->mShape->mSpeed);
        //abilityMove->regulate(serverVelocity);
        abilityMove->mShape->mCommandToRunOnShape->mVelocity->copyValuesFrom(serverVelocity);
*/
        // if distance exceeds threshold && server velocity is zero
        if(this.mAbilityMove.mDeltaPosition > this.mAbilityMove.mPosInterpLimitHigh && !this.mAbilityMove.mShape.mServerCommandCurrent.mVelocity.isZero())
        {
                this.mAbilityMove.mProcessTickStateMachine.changeState(this.mAbilityMove.mCatchupProcessTickMove);
        }
        serverVelocity = new Vector3D();
        serverVelocity.copyValuesFrom(this.mAbilityMove.mShape.mServerCommandCurrent.mVelocity);
        serverVelocity.normalise();

        if(this.mAbilityMove.mShape.mCommandToRunOnShape.mFrameTime != 0)
        {
                this.mAbilityMove.mShape.mSpeed = abilityMove.calcuateSpeed(
                this.mAbilityMove.mShape.mServerCommandCurrent.mVelocity,
                this.mAbilityMove.mShape.mCommandToRunOnShape.mFrameTime);
        }

        serverVelocity.multiply(this.mAbilityMove.mShape.mSpeed);
        //abilityMove->regulate(serverVelocity);
/*
        abilityMove->mShape->mCommandToRunOnShape->mVelocity->copyValuesFrom(serverVelocity);
*/

},

exit: function()
{

}


});

