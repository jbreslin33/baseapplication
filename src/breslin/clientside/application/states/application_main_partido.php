var ApplicationMainPartido = new Class(
{

Extends: ApplicationMain,
	
initialize: function(applicationPartido)
{
	this.parent(applicationPartido);

	this.mApplicationPartido = applicationPartido;
},

enter: function()
{
	this.parent();
},

execute: function()
{
	this.parent();

	//join game B
	if (this.mApplicationPartido.mButtonHit == this.mApplicationPartido.mButtonJoinGameB)
	{
	        this.mApplicationPartido.mButtonHit = 0;
		this.mApplicationPartido.mGame = new GamePartido(this.mApplicationPartido);
		this.mApplicationPartido.mGame.createStates();
		this.mApplicationPartido.mGame.setStates();
 		this.mApplicationPartido.sendJoinGame('2');
                this.mApplicationPartido.mStateMachine.changeState(this.mApplicationPartido.mApplicationPlay);
	}
},

exit: function()
{
	this.parent();
}

});
