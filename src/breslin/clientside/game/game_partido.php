var GamePartido = new Class(
{

Extends: Game,

initialize: function(applicationBreslin)
{
	this.parent(applicationBreslin);
	this.mMessageAskQuestion    = -76;
	this.log('GAME PARTIDO HAS BEEN CHOSEN!');
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
