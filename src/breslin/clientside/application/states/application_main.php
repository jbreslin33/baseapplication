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
	if (this.mApplicationBreslin.mButtonHit == this.mApplicationBreslin.mButtonJoinGame)
	{
	        this.mApplicationBreslin.mButtonHit = 0;
                this.mApplicationBreslin.sendJoinGame();

                this.mApplicationBreslin.mStateMachine.changeState(this.mApplicationBreslin.mApplicationPlay);
	}
	if (this.mApplicationBreslin.mButtonHit == this.mApplicationBreslin.mButtonExit)
	{
	
	}
},

exit: function()
{
        this.mApplicationBreslin.hideMainScreen();
}

});
