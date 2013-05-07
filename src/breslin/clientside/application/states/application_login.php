var ApplicationLogin = new Class(
{
	
initialize: function(application)
{
	this.mApplication = application;
},

enter: function()
{
        this.mApplication.createLoginScreen();
        this.mApplication.showLoginScreen();
},

execute: function()
{
	if (this.mApplication.mLoggedIn == true)
	{	
                this.mApplication.mStateMachine.changeState(this.mApplication.mApplicationMain);
	}

	if (this.mApplication.mButtonHit == this.mApplication.mButtonLogin)
	{
		if (this.mApplication.mLabelUsername.value == '')
		{
	        	this.mApplication.mButtonHit = 0;
			alert('username cannot be blank');
		}
		else
		{
	        	this.mApplication.mButtonHit = 0;
			this.mApplication.sendLogin();	
		}
	}
},

exit: function()
{
	this.mApplication.mStringUsername = '';
	this.mApplication.mStringPassword = '';
	
	this.mApplication.hideLoginScreen();
}

});
