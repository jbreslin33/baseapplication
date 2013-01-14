var app = require('express').createServer()
var io = require('socket.io').listen(app);

var dgram = require("dgram");
var server = dgram.createSocket("udp4");

var mMessage = 0;

app.listen(10000);

// routing
app.get('/', function (req, res) {
  res.sendfile(__dirname + '/main.html');
});

io.sockets.on('connection', function (socket) 
{
 	socket.on('browser_message', function(message,remote)
	{
		mMessage = message;
		
		//send to c++ server
		var buf = new Buffer(1);
		buf.writeInt8(-101,0);
		server.send(buf, 0, buf.length, 30004, '192.168.1.101', function(err, bytes)
		{
        		console.log('sent connect');
		});
	});
});

server.on("message", function (msg, rinfo)
{
        var type = msg.readInt8(0);
	//console.log('type:' + type);

	//let's just pass off data msg to browsers
	io.sockets.emit('news', msg)

});

server.on("listening", function ()
{
	var address = server.address();
  	console.log("server listening " +
      	address.address + ":" + address.port);
});

server.bind(41234);
