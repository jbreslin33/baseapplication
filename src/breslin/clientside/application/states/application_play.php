var ApplicationPlay = new Class(
{
	
initialize: function(applicationBreslin)
{
	this.mApplicationBreslin = applicationBreslin;
},

enter: function()
{
	this.mApplicationBreslin.mGame = new Game(this.mApplicationBreslin);
},

execute: function()
{
	if (this.mApplicationBreslin.mKey_esc)
        {
                this.mApplicationBreslin.mPlayingGame = false;

		if (this.mApplicationBreslin.mLoggedIn)
		{
                	this.mApplicationBreslin.mStateMachine.changeState(this.mApplicationBreslin.mApplicationMain);
		}
		else
		{
                	this.mApplicationBreslin.mStateMachine.changeState(this.mApplicationBreslin.mApplicationLogin);
		}
        }
        else
        {
                //game
                this.mApplicationBreslin.mGame.processUpdate();
        }
},

exit: function()
{
	this.mApplicationBreslin.mGame.quit();
	this.mApplicationBreslin.mGame = 0;
}

});
