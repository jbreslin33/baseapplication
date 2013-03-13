var ApplicationMain = new Class(
{
	
initialize: function(applicationBreslin)
{
	this.mApplicationBreslin = applicationBreslin;
},

enter: function()
{
//	this.mApplicationBreslin.log('ApplicationMain: enter');
        this.mApplicationBreslin.showMainScreen();
},

execute: function()
{
	if (this.mApplicationBreslin.mButtonHit == this.mApplicationBreslin.mButtonGame)
	{
	        this.mApplicationBreslin.mButtonHit = 0;
                this.mApplicationBreslin.sendConnect();
                this.mApplicationBreslin.mGame = new Game(this.mApplicationBreslin);

                this.mApplicationBreslin.hideMainScreen();

                this.mApplicationBreslin.mStateMachine.changeState(this.mApplicationBreslin.mApplicationPlay);
	}
	if (this.mApplicationBreslin.mButtonHit == this.mApplicationBreslin.mButtonExit)
	{
	
	}
},

exit: function()
{
//	this.mApplicationBreslin.log('ApplicationMain: exit');
}

});
