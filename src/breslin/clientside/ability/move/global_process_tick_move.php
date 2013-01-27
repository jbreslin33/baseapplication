var GlobalProcessTickMove = new Class(
{

Extends: AbilityMoveState,
initialize: function (abilityMove)
{
	this.mAbilityMove = abilityMove;
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
	this.log('Global:execute');
        this.mAbilityMove.mShape.moveGhostShape();
        this.mAbilityMove.calculateDeltaPosition();

},

exit: function()
{

}


});

