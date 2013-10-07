var GlobalProcessTickMove = new Class(
{

Extends: AbilityMoveState,
initialize: function (move)
{
	this.mMove = move;
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
        this.mMove.mShape.moveGhostShape();
        this.mMove.calculateDeltaPosition();
},

exit: function()
{

}


});

