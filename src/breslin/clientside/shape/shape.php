var Shape = new Class(
{

initialize: function()
{

},

log: function(msg)
{
	setTimeout(function()
        {
        	throw new Error(msg);
        }, 0);
}



});

