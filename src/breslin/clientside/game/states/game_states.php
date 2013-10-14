var GamePlay = new Class(
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

