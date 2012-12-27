var Network = new Class(
{

initialize: function(application,serverIP, serverPort)
{
        //application
        this.mApplicationBreslin = application;

        //server address
        this.mServerIP = serverIP;
        this.mServerPort = serverPort;

        //sequences
        this.mIncomingSequence               = 0;

	this.mSocket = this.open();

	//parse
        this.mIncomingSequence = 0;
        this.mDroppedPackets = 0;
			
},

log: function(msg)
{
        setTimeout(function()
	{
        	throw new Error(msg);
        }, 0);
},

// this should call ajax function on server to create a socket
open: function()
{
	this.log('open socket on server');
},

//this should call ajax function on server to send
send: function(byteBuffer)
{
	this.log('send:' + byteBuffer.mBuffer);
}

});

