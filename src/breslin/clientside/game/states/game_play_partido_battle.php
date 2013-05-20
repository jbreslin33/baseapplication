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
	this.log('GamePlayPartidoBattle::enter');
	this.mGame.mBattleStart = false;
	this.mGame.mApplication.createBattleScreen();
        this.mGame.mApplication.showBattleScreen();
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

        this.mGame.mApplication.hideBattleScreen();
        this.mGame.mBattleEnd = true;
}

});

