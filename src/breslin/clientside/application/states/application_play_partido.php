var ApplicationPlayPartido = new Class(
{

Extends: ApplicationPlay,
	
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
                this.mApplication.mStateMachine.changeState(this.mApplication.mApplicationLogin);
	}
/*
	if (this.mApplication.mKey_esc && this.mApplication.mSentLeaveGame == false)
        {
       		message = '';
        	this.mApplication.mNetwork.mSocket.emit('send_leave_game', message);
		this.mApplication.mSentLeaveGame = true;
        }
*/
	if (this.mApplication.mKeyArray[27] && this.mApplication.mSentLeaveGame == false)
        {
		//check to see if in battle....
		if (mApplicationPartido.getGame().mStateMachine.getCurrentState() == mApplicationPartido.getGame().mGamePlayPartidoBattle)
		{	
			mApplicationPartido.mAnswerTime = 2001;
			mApplicationPartido.mStringAnswer = 'esc';
			mApplicationPartido.sendAnswer();	
		}
		else
		{
			mApplicationPartido.mKeyArray[27] = false;
       			message = '';
        		this.mApplication.mNetwork.mSocket.emit('send_leave_game', message);
			this.mApplication.mSentLeaveGame = true;
		}
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
		if (this.mApplication.getGame())
		{
                	this.mApplication.getGame().processUpdate();
		}
        }
},

exit: function()
{
        this.mApplication.mPlayingGame = false;
	this.mApplication.mLeaveGame = false;
	if (this.mApplication.getGame())
	{
		this.mApplication.getGame().remove();
		this.mApplication.setGame(0);
	}
}

});
