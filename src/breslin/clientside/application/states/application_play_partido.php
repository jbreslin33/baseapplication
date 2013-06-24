var ApplicationPlayPartido = new Class(
{

Extends: ApplicationPlay,
	
initialize: function(applicationPartido)
{
	this.mApplicationPartido = applicationPartido;
},

enter: function()
{
	this.mApplicationPartido.mPlayingGame = true;
	this.mApplicationPartido.mSentLeaveGame = false;
},

execute: function()
{
	//check for logout as well....
   	if (this.mApplicationPartido.mLoggedIn == false)
        {
                this.mApplicationPartido.mStateMachine.changeState(this.mApplicationPartido.mApplicationLogin);
	}
	
	if (this.mApplicationPartido.mKeyArray[27] && this.mApplicationPartido.mSentLeaveGame == false)
        {
		//check to see if in battle....
		if (this.mApplicationPartido.getGame().mStateMachine.getCurrentState() == this.mApplicationPartido.getGame().mGamePlayPartidoBattle)
		{	
			this.mApplicationPartido.mAnswerTime = 3;
			this.mApplicationPartido.mStringAnswer = 'esc';
			this.mApplicationPartido.sendAnswer();	
		}
		else
		{
			this.mApplicationPartido.log('send_leave_game....');
       			message = '';
        		this.mApplicationPartido.mNetwork.mSocket.emit('send_leave_game', message);
			this.mApplicationPartido.mSentLeaveGame = true;
		}
		this.mApplicationPartido.mKeyArray[27] = false;
        }

	if (this.mApplicationPartido.mLeaveGame)
	{
		this.mApplicationPartido.log('leave game');	
		this.mApplicationPartido.mSentLeaveGame = false;
		if (this.mApplicationPartido.mLoggedIn)
		{
                	this.mApplicationPartido.mStateMachine.changeState(this.mApplicationPartido.mApplicationMain);
		}
		else
		{
                	this.mApplicationPartido.mStateMachine.changeState(this.mApplicationPartido.mApplicationLogin);
		}
	}
        else
        {
                //game
		if (this.mApplicationPartido.getGame())
		{
                	this.mApplicationPartido.getGame().processUpdate();
		}
        }
},

exit: function()
{
        this.mApplicationPartido.mPlayingGame = false;
	this.mApplicationPartido.mLeaveGame = false;
	if (this.mApplicationPartido.getGame())
	{
		this.mApplicationPartido.getGame().remove();
		this.mApplicationPartido.setGame(0);
	}
}

});
