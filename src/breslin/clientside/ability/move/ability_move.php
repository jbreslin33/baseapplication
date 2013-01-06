var AbilityMove = new Class(
{

initialize: function (shapeDynamic)
{
	//shape
    	this.mShape = shapeDynamic;
/*
        //move processTick states
        mProcessTickStateMachine = new AbilityMoveStateMachine(this);    //setup the state machine
        mProcessTickStateMachine->setCurrentState      (Normal_ProcessTick_Move::Instance());
        mProcessTickStateMachine->setPreviousState     (Normal_ProcessTick_Move::Instance());
        mProcessTickStateMachine->setGlobalState       (Global_ProcessTick_Move::Instance());

        //move interpolateTick states
        mInterpolateTickStateMachine = new AbilityMoveStateMachine(this);    //setup the state machine
        mInterpolateTickStateMachine->setCurrentState      (Normal_InterpolateTick_Move::Instance());
        mInterpolateTickStateMachine->setPreviousState     (Normal_InterpolateTick_Move::Instance());
        //mInterpolateTickStateMachine->setGlobalState       (Global_InterpolateTick_Move::Instance());
        mInterpolateTickStateMachine->setGlobalState       (NULL);



    //thresholds
    mPosInterpLimitHigh = .066f; //how far away from server till we try to catch up
    mPosInterpFactor    = 4.0f;
        mMaximunVelocity    = .003083f; //do not let velocity go above this in any direction.

        //deltas
        mDeltaX        = 0.0f;
        mDeltaY            = 0.0f;
        mDeltaZ        = 0.0f;
        mDeltaPosition = 0.0f;
*/
	this.mAbilityGlobalProcessTickMove  = new AbilityGlobalProcessTickMove(this); 
	this.mAbilityCatchupProcessTickMove = new AbilityCatchupProcessTickMove(this); 
	this.mAbilityNormalProcessTickMove  = new AbilityNormalProcessTickMove(this); 
        
	//move processTick states
        this.mProcessTickStateMachine       = new AbilityMoveStateMachine(this);    //setup the state machine

        this.mProcessTickStateMachine.setCurrentState      (this.mAbilityNormalProcessTickMove);
        this.mProcessTickStateMachine.setPreviousState     (this.mAbilityNormalProcessTickMove);
        this.mProcessTickStateMachine.setGlobalState       (this.mAbilityGlobalProcessTickMove);

},

log: function(msg)
{
        setTimeout(function()
        {
                throw new Error(msg);
        }, 0);
},

processTick: function()
{

},

interpolateTick: function(renderTime)
{
	this.log('intermove:' + renderTime);
}

});


/******************************************************
*                               UPDATING
********************************************************/
/*
void AbilityMove::processTick()
{
        mProcessTickStateMachine->update();
}
void AbilityMove::interpolateTick(float renderTime)
{
        mInterpolateTickStateMachine->update();
}
*/
/******************************************************
*                               MOVE
********************************************************/
/*
void AbilityMove::calculateDeltaPosition()  //mov
{

        mDeltaX = mShape->mServerCommandCurrent->mPosition->x - mShape->getPosition()->x;
        mDeltaY = mShape->mServerCommandCurrent->mPosition->y - mShape->getPosition()->y;
        mDeltaZ = mShape->mServerCommandCurrent->mPosition->z - mShape->getPosition()->z;

        //distance we are off from server
        mDeltaPosition = sqrt(pow(mDeltaX, 2) + pow(mDeltaY, 2) +  pow(mDeltaZ, 2));
}

float AbilityMove::calcuateSpeed(Vector3D* velocity, int frameTime)
{
        float speed = sqrt(
        pow(velocity->x, 2) +
        pow(velocity->y, 2) +
        pow(velocity->z, 2)) /
        frameTime;

        return speed;
}

*/

