var AbilityMove = new Class(
{

initialize: function (shapeDynamic)
{
	//shape
    	this.mShape = shapeDynamic;
	
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

/******************************************************
*                               UPDATING
********************************************************/
processTick: function()
{
        this.mProcessTickStateMachine.update();
},

interpolateTick: function(renderTime)
{
        this.mInterpolateTickStateMachine.update();
},

/******************************************************
*                               MOVE
********************************************************/
calculateDeltaPosition: function()
{
        this.mDeltaX = this.mShape.mServerCommandCurrent.mPosition.x - this.mShape.getPosition().x;
        this.mDeltaY = this.mShape.mServerCommandCurrent.mPosition.y - this.mShape.getPosition().y;
        this.mDeltaZ = this.mShape.mServerCommandCurrent.mPosition.z - this.mShape.getPosition().z;

        //distance we are off from server
        mDeltaPosition = Math.sqrt(Math.pow(this.mDeltaX, 2) + Math.pow(this.mDeltaY, 2) +  Math.pow(this.mDeltaZ, 2));
},

calculateSpeed: function(velocity,frameTime)
{
/*
        float speed = sqrt(
        pow(velocity->x, 2) +
        pow(velocity->y, 2) +
        pow(velocity->z, 2)) /
        frameTime;

        return speed;
*/
}

});
