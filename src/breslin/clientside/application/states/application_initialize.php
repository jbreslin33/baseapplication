var ApplicationInitialize = new Class(
{
	
initialize: function(application)
{
	this.mApplication = application;
},

enter: function()
{
},

execute: function()
{
        if (this.mApplication.setup())
        {
        	this.mApplication.mSetup = true;
        }
        if (this.mApplication.mSetup && this.mApplication.mConnected)
	{
		this.mApplication.hideLoadingScreen();
        	this.mApplication.mStateMachine.changeState(this.mApplication.mApplicationLogin);

	}
},

exit: function()
{
}

});
