var ByteBuffer = new Class(
{
	
initialize: function()
{
	this.mBuffer = 0;
},

writeByte: function(b)
{
	this.mBuffer += b;
}


});
