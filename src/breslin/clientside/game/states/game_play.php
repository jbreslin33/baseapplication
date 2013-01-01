var GamePlay = new Class(
{

initialize: function(game)
{
	this.mGame = game; 
},

enter: function()
{

},

execute: function()
{
	//user input
        this.mGame.processInput();

        //network outgoing
        this.mGame.sendByteBuffer();

	/********** let's try to do this with delay *****/
       	if (this.mGame.mPollDelayCounter > this.mGame.mPollDelay)
	{ 
		//network ingoing
        	this.mGame.checkForByteBuffer();
		
		//reset counter
		this.mGame.mPollDelayCounter = 0;
	}
	
	this.mGame.mPollDelayCounter++;	


},

exit: function()
{

}

});

