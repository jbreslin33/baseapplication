var ApplicationPlay = new Class(
{
	
initialize: function(application)
{
	this.mApplication = application;
},

enter: function()
{
	this.mApplication.mPlayingGame = true;
	this.mApplication.mSentLeaveGame = false;
},

execute: function()
{
	//check for logout as well....
   	if (this.mApplication.mLoggedIn == false)
        {
		this.mApplication.log('mLoggedIN = false');
                this.mApplication.mStateMachine.changeState(this.mApplication.mApplicationLogin);
	}
	if (this.mApplication.mKey_q && this.mApplication.mSentLeaveGame == false)
        {
       		message = '';
        	this.mApplication.mNetwork.mSocket.emit('send_quit_game', message);
		this.mApplication.mSentLeaveGame = true;
        }

	if (this.mApplication.mLeaveGame)
	{
		this.mApplication.mSentLeaveGame = false;
		if (this.mApplication.mLoggedIn)
		{
                	this.mApplication.mStateMachine.changeState(this.mApplication.mApplicationMain);
		}
		else
		{
                	this.mApplication.mStateMachine.changeState(this.mApplication.mApplicationLogin);
		}
	}
        else
        {
                //game
                this.mApplication.mGame.processUpdate();
        }
},

exit: function()
{
        this.mApplication.mPlayingGame = false;
	this.mApplication.mLeaveGame = false;
	if (this.mApplication.mGame)
	{
		this.mApplication.mGame.remove();
		this.mApplication.mGame = 0;
	}
}

});
