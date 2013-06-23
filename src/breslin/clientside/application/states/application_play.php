var ApplicationPlay = new Class(
{
	
initialize: function(applicationBreslin)
{
	this.mApplicationBreslin = application;
},

enter: function()
{
	this.mApplicationBreslin.mPlayingGame = true;
	this.mApplicationBreslin.mSentLeaveGame = false;
},

execute: function()
{
	//check for logout as well....
   	if (this.mApplicationBreslin.mLoggedIn == false)
        {
                this.mApplicationBreslin.mStateMachine.changeState(this.mApplicationBreslin.mApplicationLogin);
	}
	
	if (mApplicationBreslin.mKeyArray[27] && mApplicationBreslin.mSentLeaveGame == false)
	{
		message = '';
                this.mApplicationBreslin.mNetwork.mSocket.emit('send_leave_game', message);
                this.mApplicationBreslin.mSentLeaveGame = true;
	}

	if (this.mApplicationBreslin.mLeaveGame)
	{
		this.mApplicationBreslin.mSentLeaveGame = false;
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
		if (this.mApplicationBreslin.getGame())
		{
                	this.mApplicationBreslin.getGame().processUpdate();
		}
        }
},

exit: function()
{
        this.mApplicationBreslin.mPlayingGame = false;
	this.mApplicationBreslin.mLeaveGame = false;
	if (this.mApplicationBreslin.getGame())
	{
		this.mApplicationBreslin.getGame().remove();
		this.mApplicationBreslin.setGame(0);
	}
}

});
