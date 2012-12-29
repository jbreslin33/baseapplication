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

	/********** let's try to do this every 1 sec *****/
       	if (this.mGame.mPollDelayCounter > this.mGame.mPollDelay)
	{ 
		//network ingoing
        	this.mGame.checkForByteBuffer();
		
		//reset counter
		this.mGame.mPollDelayCounter = 0;
	}
	
	//increment counter
	this.mGame.mPollDelayCounter++;	
},

exit: function()
{

}

});

