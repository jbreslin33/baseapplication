var GlobalProcessTickMove = new Class(
{

Extends: AbilityMoveState,
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

enter: function(abilityMove)
{

},

execute: function(abilityMove)
{
	this.log('Global:execute');
},

exit: function(abilityMove)
{

}


});

