var GamePlayPartidoBattle = new Class(
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
	this.mGame.mBattleStart = false;
},

execute: function()
{

	//user input
        this.mGame.processInput();

        //network outgoing
        this.mGame.sendByteBuffer();
},	

exit: function()
{

}

});

