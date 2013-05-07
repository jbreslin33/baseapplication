var ApplicationMain = new Class(
{
	
initialize: function(application)
{
	this.mApplication = application;
},

enter: function()
{
        this.mApplication.createMainScreen();
        this.mApplication.showMainScreen();
},

execute: function()
{
	//join game A
	if (this.mApplication.mButtonHit == this.mApplication.mButtonJoinGameA)
	{
	        this.mApplication.mButtonHit = 0;
		this.mApplication.mGame = new Game(this.mApplication);
		this.mApplication.mGame.createStates();
		this.mApplication.mGame.setStates();
 		this.mApplication.sendJoinGame('1');
                this.mApplication.mStateMachine.changeState(this.mApplication.mApplicationPlay);
	}

	//logout
	if (this.mApplication.mButtonHit == this.mApplication.mButtonLogout)
	{
	        this.mApplication.mButtonHit = 0;
                this.mApplication.sendLogout();
	}

	if (this.mApplication.mLoggedIn == false)
	{
                this.mApplication.mStateMachine.changeState(this.mApplication.mApplicationLogin);
	}

	//exit
	if (this.mApplication.mButtonHit == this.mApplication.mButtonExit)
	{
	        this.mApplication.mButtonHit = 0;
	
	}
},

exit: function()
{
        this.mApplication.hideMainScreen();
}

});
