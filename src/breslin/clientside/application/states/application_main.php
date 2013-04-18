var ApplicationMain = new Class(
{
	
initialize: function(applicationBreslin)
{
	this.mApplicationBreslin = applicationBreslin;
},

enter: function()
{
        this.mApplicationBreslin.createMainScreen();
        this.mApplicationBreslin.showMainScreen();
},

execute: function()
{
	//join game A
	if (this.mApplicationBreslin.mButtonHit == this.mApplicationBreslin.mButtonJoinGameA)
	{
	        this.mApplicationBreslin.mButtonHit = 0;
		this.mApplicationBreslin.mGame = new Game(this.mApplicationBreslin);
 		this.mApplicationBreslin.sendJoinGame('1');
                this.mApplicationBreslin.mStateMachine.changeState(this.mApplicationBreslin.mApplicationPlay);
	}

	//join game B
	if (this.mApplicationBreslin.mButtonHit == this.mApplicationBreslin.mButtonJoinGameB)
	{
	        this.mApplicationBreslin.mButtonHit = 0;
		this.mApplicationBreslin.mGame = new Game(this.mApplicationBreslin);
 		this.mApplicationBreslin.sendJoinGame('2');
                this.mApplicationBreslin.mStateMachine.changeState(this.mApplicationBreslin.mApplicationPlay);
	}

	//logout
	if (this.mApplicationBreslin.mButtonHit == this.mApplicationBreslin.mButtonLogout)
	{
	        this.mApplicationBreslin.mButtonHit = 0;
                this.mApplicationBreslin.sendLogout();
	}

	if (this.mApplicationBreslin.mLoggedIn == false)
	{
                this.mApplicationBreslin.mStateMachine.changeState(this.mApplicationBreslin.mApplicationLogin);
	}

	//exit
	if (this.mApplicationBreslin.mButtonHit == this.mApplicationBreslin.mButtonExit)
	{
	        this.mApplicationBreslin.mButtonHit = 0;
	
	}
},

exit: function()
{
        this.mApplicationBreslin.hideMainScreen();
}

});
