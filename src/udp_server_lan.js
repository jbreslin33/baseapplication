var app = require('express').createServer()
var io = require('socket.io').listen(app);

var dgram = require("dgram");
var server = dgram.createSocket("udp4");

var mMessage = 0;

app.listen(10000);

	console.log('ip match with tp');
	app.get('/', function (req, res) 
	{
  		res.sendfile(__dirname + '/main_lan.html');
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
	//constants
	mCommandOriginX      = 4;
	mCommandOriginY      = 8;
	mCommandOriginZ      = 16;
	mCommandRotationX    = 32;
	mCommandRotationZ    = 64;

	//to break out of message when it's over
	var length = msg.length;
	var count = 0;

	//type
        var type   = msg.readInt8(count);
	count++;

	//begin our dataString that will be sent to browser clients	
	var dataString = type;  
	
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
	
		//let's just pass off data msg to browsers
		datastring = dataString + "," + client + "," + index + "," + xpos + "," + ypos + "," + zpos + "," + xrot + "," + zrot + "," + mesh + "," + anim; 

		io.sockets.emit('news', datastring)
	}

	if (type == 1)
	{
		//sequence
        	dataString = dataString + "," + msg.readUInt16LE(count);
		count = count + 2;

		//frametime			
		dataString = dataString + "," + msg.readInt8(count);
		count++;
	
		while(count < length)
		{
			var flags = 0;

        		moveXChanged = true;
        		moveYChanged = true;
        		moveZChanged = true;
		
			//index(id)	
			dataString = dataString + "," +  msg.readInt8(count);
			count++;
	
			//flag	
			flags = msg.readInt8(count);
			dataString = dataString + "," + flags;
			count++;

        		// Origin
        		if(flags & mCommandOriginX)
        		{
        			dataString = dataString + "," + msg.readFloatLE(count);
				count = count + 4;
        		}
        		else
        		{
                		moveXChanged = false;
        		}

        		if(flags & mCommandOriginY)
        		{
        			dataString = dataString + "," + msg.readFloatLE(count);
				count = count + 4;
			}
        		else
        		{
                		moveYChanged = false;
        		}

        		if(flags & mCommandOriginZ)
        		{
        			dataString = dataString + "," + msg.readFloatLE(count);
				count = count + 4;
        		}
        		else
        		{
                		moveZChanged = false;
        		}

        		//rotation
        		if(flags & mCommandRotationX)
        		{
        			dataString = dataString + "," + msg.readFloatLE(count);
				count = count + 4;
        		}

        		if(flags & mCommandRotationZ)
        		{
        			dataString = dataString + "," + msg.readFloatLE(count);
				count = count + 4;
        		}
		
		} //end if
		console.log("dataString:" + dataString);	
		io.sockets.emit('news', datastring)
	}
});

server.on("listening", function ()
{
	var address = server.address();
  	console.log("server listening " +
      	address.address + ":" + address.port);
});

server.bind(41234);
