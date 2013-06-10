var GamePlayPartidoBattle = new Class(
{

initialize: function(gamePartido)
{
	this.mGamePartido = gamePartido; 
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
	this.mGamePartido.mApplicationPartido.createBattleScreen();
	this.mGamePartido.mApplicationPartido.showBattleScreen();
	this.mGamePartido.mBattleStart = false;

	
	//reset text box	
	//still need to do this.....

},

execute: function()
{
	if (this.mGamePartido.mBattleEnd)
        {
		this.log('battle end!!!!!!!!!!!###$$$');
               this.mGamePartido.mStateMachine.changeState(this.mGamePartido.mGamePlay);
        }
},	

exit: function()
{
        this.mGamePartido.mApplicationPartido.hideBattleScreen();
        this.mGamePartido.mBattleEnd   = false;
        this.mGamePartido.mBattleStart = false;
}

});

