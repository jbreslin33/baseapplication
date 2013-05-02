var GamePartidoPlay = new Class(
{

initialize: function(game)
{
	this.mGame = game; 
},

log: function(msg)
{
        setTimeout(function()
        {
                throw new Error(msg);
        }, 0);
},

enter: function()
{

},

execute: function()
{
        if (mGame.mBattleStart)
        {
                mGame.mStateMachine.changeState(mGame.mGameBattle);
        }

	//user input
        this.mGame.processInput();

        //network outgoing
        this.mGame.sendByteBuffer();
},	

exit: function()
{

}

});

