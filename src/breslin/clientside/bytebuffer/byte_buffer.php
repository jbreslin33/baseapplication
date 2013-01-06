var ByteBuffer = new Class(
{
	
initialize: function()
{
	this.mBuffer = new Array();
	this.mReadCount = 0;	
},

writeByte: function(b)
{
	this.mBuffer[this.mReadCount] = b;
	this.mReadCount++
},

beginReading: function()
{
        this.mReadCount = 0;
},

readByte: function()
{
	return this.mBuffer[this.mReadCount];
}


});
