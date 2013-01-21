var GamePlay = new Class(
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

},

execute: function()
{
	//user input
        this.mGame.processInput();

        //network outgoing
        this.mGame.sendByteBuffer();
	

	//don't need to do this as it's being done in main.html
       	/*	
	if (this.mGame.mPollDelayCounter > this.mGame.mPollDelay)
	{ 
		//network ingoing
        	this.mGame.checkForByteBuffer();
		
		//reset counter
		this.mGame.mPollDelayCounter = 0;
	}
	
	this.mGame.mPollDelayCounter++;	
	*/

},

exit: function()
{

}

});

