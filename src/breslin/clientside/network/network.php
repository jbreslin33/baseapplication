var Network = new Class(
{

initialize: function(application,serverIP, serverPort)
{
	//client id
	this.mClientID = 0;

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
	//return io.connect('71.23.229.73:10000');
	//return io.connect('192.168.1.101:10000');
	return io.connect('192.168.2.88:10000');
	//return io.connect('192.168.2.234:10000');
},

sendConnect: function()
{
	this.mSocket.emit('send_connect', '-111');
}

});
