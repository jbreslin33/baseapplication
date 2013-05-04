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
	this.log('GamePlayPartidoBattle enter');
	this.mGame.mBattleStart = false;
},

execute: function()
{
	this.log('GamePlayPartidoBattle execute');

	//user input
        this.mGame.processInput();

        //network outgoing
        this.mGame.sendByteBuffer();
},	

exit: function()
{

}

});

