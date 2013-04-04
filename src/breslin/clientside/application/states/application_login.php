var ApplicationLogin = new Class(
{
	
initialize: function(applicationBreslin)
{
	this.mApplicationBreslin = applicationBreslin;
},

enter: function()
{
        this.mApplicationBreslin.createLoginScreen();
        this.mApplicationBreslin.showLoginScreen();
},

execute: function()
{
	if (this.mApplicationBreslin.mLoggedIn == true)
	{	
                this.mApplicationBreslin.mStateMachine.changeState(this.mApplicationBreslin.mApplicationMain);
	}

	if (this.mApplicationBreslin.mButtonHit == this.mApplicationBreslin.mButtonLogin)
	{
		if (this.mApplicationBreslin.mLabelUsername.value == '')
		{
	        	this.mApplicationBreslin.mButtonHit = 0;
			alert('username cannot be blank');
		}
		else
		{
	        	this.mApplicationBreslin.mButtonHit = 0;
			this.mApplicationBreslin.sendLogin();	
		}
	}
},

exit: function()
{
	this.mApplicationBreslin.mStringUsername = '';
	this.mApplicationBreslin.mStringPassword = '';
	
	this.mApplicationBreslin.hideLoginScreen();
}

});
