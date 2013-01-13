var app = require('express').createServer()
var io = require('socket.io').listen(app);

var dgram = require("dgram");
var server = dgram.createSocket("udp4");

var mMessage = 0;

app.listen(8000);

// routing
app.get('/', function (req, res) {
  res.sendfile(__dirname + '/main.html');
});

io.sockets.on('connection', function (socket) 
{
        console.log('xxx connection');
 	socket.on('browser_message', function(message,remote)
	{
		mMessage = message;
        	console.log('xxx message' + mMessage);
		//send to c++ server
		var PORT = 33333;
		var HOST = '192.168.1.101';

		var buf = new Buffer(1);
		buf.writeInt8(-101,0);
		server.send(buf, 0, buf.length, 30004, HOST, function(err, bytes)
		{
        		console.log('sent connect');
		});
	});
});


server.on("message", function (msg, rinfo)
{
//console.log("server got: " + msg + " from " +
 //   rinfo.address + ":" + rinfo.port);

        var type = msg.readInt8(0);
	console.log('type:' + type);
});

server.on("listening", function () {
  var address = server.address();
  console.log("server listening " +
      address.address + ":" + address.port);
});

server.bind(41234);


/*
	app.on('message', function (message, remote)
	{
        	//var type = message.readInt8(0);

        	//console.log(remote.address + ':' + remote.port +' - ' + type);
		console.log('against the wind');
	});
*/

//});
/*
app.on('message', function (message, remote)
{
        //var type = message.readInt8(0);

        //console.log(remote.address + ':' + remote.port +' - ' + type);
	console.log('against the wind');
});
*/




//var io = require('socket.io').listen(app);


/*
server.listen(8000);

// routing
app.get('/', function (req, res)
{
	res.sendfile(__dirname + '/main.html');
});

server.on('listening', function ()
{
	var address = server.address();
    	console.log('UDP Server listening on ' + address.address + ":" + address.port);
});

server.on('connect', function ()
{
	console.log('successfully established a working connection \o/');
});

server.on('message', function (message, remote)
{
	var type = message.readInt8(0);
	
    	console.log(remote.address + ':' + remote.port +' - ' + type);
});
*/

/*
var PORT = 33333;
var HOST = '192.168.1.101';

var dgram = require('dgram');
var server = dgram.createSocket('udp4');
*/
//server.bind(PORT, HOST);

//send connect
var buf = new Buffer(1);
buf.writeInt8(-101,0);
/*
server.send(buf, 0, buf.length, 30004, HOST, function(err, bytes)
{
	console.log('sent connect');
});
*/

