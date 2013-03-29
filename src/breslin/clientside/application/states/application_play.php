var ApplicationPlay = new Class(
{
	
initialize: function(applicationBreslin)
{
	this.mApplicationBreslin = applicationBreslin;
},

enter: function()
{
	this.mApplicationBreslin.mGame = new Game(this.mApplicationBreslin);
	this.mApplicationBreslin.mPlayingGame = true;
	this.mApplicationBreslin.mSentLeaveGame = false;
},

execute: function()
{

	if (this.mApplicationBreslin.mKey_q && this.mApplicationBreslin.mSentLeaveGame == false)
        {
		
       		message = '';
        	this.mApplicationBreslin.mNetwork.mSocket.emit('send_quit_game', message);
		this.mApplicationBreslin.log('send_quit_game');
		this.mApplicationBreslin.mSentLeaveGame = true;
        }

	if (this.mApplicationBreslin.mLeaveGame)
	{
		this.mApplicationBreslin.mSentLeaveGame = false;
		this.mApplicationBreslin.log('got mLeaveGame var change');
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
        this.mApplicationBreslin.mPlayingGame = false;
	this.mApplicationBreslin.mLeaveGame = false;
	this.mApplicationBreslin.mGame.quit();
}

});
