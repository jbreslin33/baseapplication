var ApplicationInitialize = new Class(
{
	
initialize: function(applicationBreslin)
{
	this.mApplicationBreslin = applicationBreslin;
},

enter: function()
{
},

execute: function()
{
        if (this.mApplicationBreslin.setup())
        {
        	this.mApplicationBreslin.mSetup = true;
        }
        if (this.mApplicationBreslin.mSetup && this.mApplicationBreslin.mConnected)
	{
		this.mApplicationBreslin.hideLoadingScreen();
        	this.mApplicationBreslin.mStateMachine.changeState(this.mApplicationBreslin.mApplicationLogin);

	}
},

exit: function()
{
}

});
