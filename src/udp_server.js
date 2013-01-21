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
	
		//let's just pass off data msg to browsers
		var datastring = type + "," + client + "," + index + "," + xpos + "," + ypos + "," + zpos + "," + xrot + "," + zrot + "," + mesh + "," + anim; 
		io.sockets.emit('news', datastring)
	}

	if (type == 1)
	{
		
		//constants
		mCommandOriginX      = 4;
		mCommandOriginY      = 8;
		mCommandOriginZ      = 16;
		mCommandRotationX    = 32;
		mCommandRotationZ    = 64;


        	var s = msg.readUInt16LE(1);
		var dataString = s;  
        	
		var f = msg.readInt8(3);
		dataString = dataString + f;
		
		var id = msg.readInt8(4);
		dataString = dataString + id;
		
		var flags = msg.readInt8(5);
		dataString = dataString + flags;

        	// Origin
        	if(flags & mCommandOriginX)
        	{
                	//mServerCommandLast->mPosition->x = mServerCommandCurrent->mPosition->x;
                	//mServerCommandCurrent->mPosition->x = mes->ReadFloat();
        		var xpos   = msg.readFloatLE(6);
			dataString
        	}
        	else
        	{
                	moveXChanged = false;
        	}

        	if(flags & mCommandOriginY)
        	{
                	mServerCommandLast->mPosition->y = mServerCommandCurrent->mPosition->y;
                	mServerCommandCurrent->mPosition->y = mes->ReadFloat();
        	}
        	else
        	{
                	moveYChanged = false;
        	}

        	if(flags & mCommandOriginZ)
        	{
                	mServerCommandLast->mPosition->z = mServerCommandCurrent->mPosition->z;
                	mServerCommandCurrent->mPosition->z = mes->ReadFloat();
        	}
        	else
        	{
                	moveZChanged = false;
        	}

        	//rotation
        	if(flags & mCommandRotationX)
        	{
                	mServerCommandLast->mRotation->x = mServerCommandCurrent->mRotation->x;
                	mServerCommandCurrent->mRotation->x = mes->ReadFloat();
        	}

        	if(flags & mCommandRotationZ)
        	{
                	mServerCommandLast->mRotation->z = mServerCommandCurrent->mRotation->z;
                	mServerCommandCurrent->mRotation->z = mes->ReadFloat();
        	}

	}


});

server.on("listening", function ()
{
	var address = server.address();
  	console.log("server listening " +
      	address.address + ":" + address.port);
});

server.bind(41234);
