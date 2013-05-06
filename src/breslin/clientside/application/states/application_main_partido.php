var ApplicationMainPartido = new Class(
{

Extends: ApplicationMain,
	
initialize: function(application)
{
	this.parent(application);

	this.mApplication = application;
},

enter: function()
{
	this.parent();
},

execute: function()
{
	this.parent();

	//join game B
	if (this.mApplication.mButtonHit == this.mApplication.mButtonJoinGameB)
	{
	        this.mApplication.mButtonHit = 0;
		this.mApplication.mGame = new GamePartido(this.mApplication);
 		this.mApplication.sendJoinGame('2');
                this.mApplication.mStateMachine.changeState(this.mApplication.mApplicationPlay);
	}
},

exit: function()
{
	this.parent();
}

});
