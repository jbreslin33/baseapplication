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


/*
client->mMessage.WriteByte(mIndex);

        client->mMessage.WriteFloat(mSceneNode->getPosition().x);
        client->mMessage.WriteFloat(mSceneNode->getPosition().y);
        client->mMessage.WriteFloat(mSceneNode->getPosition().z);

        client->mMessage.WriteFloat(mRotation->x);
        client->mMessage.WriteFloat(mRotation->z);

        //mesh
        client->mMessage.WriteByte(mMeshCode);

        //animation
        client->mMessage.WriteByte(mAnimated);

*/
server.on("message", function (msg, rinfo)
{
        var type   = msg.readInt8(0);
	
	//add shape
	if (type == -103)
	{ 
		console.log('length:' + msg.length);
        	var client = msg.readInt8(1);
        	var index  = msg.readInt8(2);
        	var xpos   = msg.readFloatLE(3);
        	var ypos   = msg.readFloatLE(7);
        	var zpos   = msg.readFloatLE(11);
        	var xrot   = msg.readFloatLE(15);
        	var zrot   = msg.readFloatLE(19);
        	var mesh   = msg.readInt8(23);
        	var anim   = msg.readInt8(24);
		console.log('t:' + type + 'c:' + client + 'i:' + index + 'x:' + xpos + 'y:' + ypos + 'z:' + zpos + 'x:' + xrot + 'z:' + zrot + 'm:' + mesh + 'a:' + anim);
	}

	if (type == 1)
	{


	}

	//let's just pass off data msg to browsers
	var datastring = type + "," + client + "," + index + "," + xpos + "," + ypos; 
	io.sockets.emit('news', datastring)

});

server.on("listening", function ()
{
	var address = server.address();
  	console.log("server listening " +
      	address.address + ":" + address.port);
});

server.bind(41234);
