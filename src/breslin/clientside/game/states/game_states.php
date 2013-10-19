var PLAY_GAME = new Class(
{
Extends: State,

initialize: function()
{
},

log: function(msg)
{
        setTimeout(function()
        {
                throw new Error(msg);
        }, 0);
},

enter: function(game)
{

},

execute: function(game)
{
	//user input
        game.processInput();

        //network outgoing
        game.sendByteBuffer();
},	

exit: function(game)
{

}

});

var RESET_GAME = new Class(
{
Extends: State,

initialize: function()
{
},

log: function(msg)
{
        setTimeout(function()
        {
                throw new Error(msg);
        }, 0);
},

enter: function(game)
{
	this.log('RESET_GAME::enter');
	game.mApplication.createResetScreen();
        game.mApplication.showResetScreen();
  
	for (i = 0; i < game.mShapeVector.length; i++)
        {
                game.mShapeVector[i].setVisible(false);
        }
},

execute: function(game)
{
},

exit: function(game)
{
        game.mApplication.hideResetScreen();
	
	for (i = 0; i < game.mShapeVector.length; i++)
        {
                game.mShapeVector[i].setVisible(true);
        }
}

});

