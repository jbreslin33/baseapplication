var AbilityMoveStateMachine = new Class(
{

initialize: function()
{
	this.mCurrentState = 0;
	this.mPreviousState = 0;
	this.mGlobalState = 0;
},

setCurrentState: function(s)
{
	this.mCurrentState = s;
},


setGlobalState: function(s)
{
	this.mGlobalState = s;
},


setPreviousState: function(s)
{
	this.mPreviousState = s;
},

update: function()
{
	if(this.mGlobalState)
	{
		this.mGlobalState.execute();
	}
	if (this.mCurrentState)
	{
		this.mCurrentState.execute();
	}
},

changeState: function(pNewState)
{
	this.mPreviousState = this.mCurrentState;

	if(this.mCurrentState)
	{
       		this.mCurrentState.exit();
	}

	this.mCurrentState = pNewState;

	if(this.mCurrentState)
	{
        	this.mCurrentState.enter();
	}
}

});
