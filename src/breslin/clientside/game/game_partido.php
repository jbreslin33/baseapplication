var GamePartido = new Class(
{

Extends: Game,

initialize: function(applicationBreslin)
{
	this.parent(applicationBreslin);

	//states
        this.mGamePlay = new GamePlayPartido(this);
        this.mGameBattle = new GamePlayPartidoBattle(this);

	//constants	
	//questions
	this.mMessageAskQuestion    = -76;
		
	//battle
	this.mMessageBattleStart = -75;
	this.mMessageBattleEnd   = -74;

	this.mBattleStart = false;
	this.mBattleEnd = false;
},


log: function(msg)
{
	setTimeout(function()
        {
        	throw new Error(msg);
        }, 0);
},

askQuestion: function(byteBuffer)
{
	this.log('game askQuestion');
},

battleStart: function(byteBuffer)
{
	this.log('game battleStart');
},

battleEnd: function(byteBuffer)
{
	this.log('game battleEnd');
}

});
