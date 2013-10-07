var GlobalProcessTickMove = new Class(
{

Extends: State,
initialize: function ()
{
},

log: function(msg)
{
        setTimeout(function()
        {
                throw new Error(msg);
        }, 0);
},

enter: function(move)
{

},

execute: function(move)
{
        move.mShape.moveGhostShape();
        move.calculateDeltaPosition();
},

exit: function(move)
{

}


});

