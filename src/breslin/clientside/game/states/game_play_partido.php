var GamePlayPartido = new Class(
{

Extends: GamePlay,


initialize: function(gamePartido)
{
	this.parent(gamePartido);
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
	this.parent();
},

execute: function()
{
        if (this.mGamePartido.mBattleStart)
        {
                this.mGamePartido.mStateMachine.changeState(this.mGamePartido.mGamePlayPartidoBattle);
        }
        
        if (this.mGamePartido.mApplicationPartido.mGameReset)
        {
                this.mGamePartido.mStateMachine.changeState(this.mGamePartido.mGamePlayPartidoReset);
        }

	this.parent()
},	

exit: function()
{
	this.parent();
}

});

