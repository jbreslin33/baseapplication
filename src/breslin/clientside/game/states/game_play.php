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
        //this.mGame->sendByteBuffer();

        //network ingoing
        //this.mGame->checkForByteBuffer();
},

exit: function()
{

}

});

