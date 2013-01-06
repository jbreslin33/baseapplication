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
},

processTick: function()
{

},

interpolateTick: function(renderTime)
{

}

});

