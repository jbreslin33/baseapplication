var app = require('express').createServer()
var io = require('socket.io').listen(app);

app.listen(8000);

// routing
app.get('/', function (req, res) {
  res.sendfile(__dirname + '/main.html');
});

app.on('connection', function ()
{
        console.log('successfully established a working connection \o/');
});





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
