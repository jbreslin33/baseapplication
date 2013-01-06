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
	this.mGlobalProcessTickMove  = new GlobalProcessTickMove(this); 
	this.mCatchupProcessTickMove = new CatchupProcessTickMove(this); 
	this.mNormalProcessTickMove  = new NormalProcessTickMove(this); 
        
	//move processTick states
        this.mProcessTickStateMachine       = new AbilityMoveStateMachine(this);    //setup the state machine

        this.mProcessTickStateMachine.setCurrentState      (this.mNormalProcessTickMove);
        this.mProcessTickStateMachine.setPreviousState     (this.mNormalProcessTickMove);
        this.mProcessTickStateMachine.setGlobalState       (this.mGlobalProcessTickMove);

	//interpolate
	this.mNormalInterpolateTickMove  = new NormalInterpolateTickMove(this); 
       
	//move interpolateTick states
        this.mInterpolateTickStateMachine = new AbilityMoveStateMachine(this);    //setup the state machine
        this.mInterpolateTickStateMachine.setCurrentState      (this.mNormalInterpolateTickMove);
        this.mInterpolateTickStateMachine.setPreviousState     (this.mNormalInterpolateTickMove);
        this.mInterpolateTickStateMachine.setGlobalState       (0);
    
	//thresholds
    	this.mPosInterpLimitHigh = .066; //how far away from server till we try to catch up
    	this.mPosInterpFactor    = 4.0;
        this.mMaximunVelocity    = .003083; //do not let velocity go above this in any direction.

        //deltas
        this.mDeltaX        = 0.0;
        this.mDeltaY        = 0.0;
        this.mDeltaZ        = 0.0;
        this.mDeltaPosition = 0.0;
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
//	this.log('intermove:' + renderTime);
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

