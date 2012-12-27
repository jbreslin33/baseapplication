var ByteBuffer = new Class(
{
	
initialize: function()
{
	this.mBuffer = '';
},

writeByte: function(b)
{
	this.mBuffer += b;
}


});
