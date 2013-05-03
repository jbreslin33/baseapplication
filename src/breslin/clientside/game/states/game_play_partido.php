var GamePlayPartido = new Class(
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
	this.log('GamePlayPartido execute');
        if (this.mGame.mBattleStart)
        {
                this.mGame.mStateMachine.changeState(this.mGame.mGamePartidoPlayBattle);
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

