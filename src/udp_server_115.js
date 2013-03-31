var app = require('express').createServer()
var io = require('socket.io').listen(app);
io.set('log level', 1); //reduce logging
var dgram = require("dgram");
var server = dgram.createSocket("udp4");

var mMessage = 0;

var mClientIDCounter = 0;

var skipCounter = 0; 
var fireNumber = 0; //no skipping of frames

//constants
mCommandOriginX      = 4;
mCommandOriginY      = 8;
mCommandOriginZ      = 16;
mCommandRotationX    = 32;
mCommandRotationZ    = 64;

mServerIP = '192.168.1.115';
mServerPort = 30004;


app.listen(10000);

// routing
app.get('/', function (req, res) {
  res.sendfile(__dirname + '/main_115.html');
});


//when a browser client first connects, this get's called.
//then we parlay that into a send to the c++ server
//could i not just assign an id here and then pass that to c++ as it's just going to be a browser id and no one else will use it.


io.sockets.on('connection', function (socket) 
{
        socket.on('send_connect', function(message,remote)
        {
		socket.join('game1');
                mMessage = message;
               
		mess = parseInt(mMessage);
 
                //send to c++ server
                var buf = new Buffer(2);
                buf.writeInt8(mess,0);

		mClientIDCounter++;
		console.log('clientID socket connect:' + socket.mClientID);
		socket.mClientID = mClientIDCounter;
                
		buf.writeInt8(socket.mClientID,1);

                server.send(buf, 0, buf.length, mServerPort, mServerIP, function(err, bytes)
                {
                });
        });

        socket.on('send_join_game', function(message,remote)
	{
                //send to c++ server
                var buf = new Buffer(2);

		//type
                type = -117;
                buf.writeInt8(type,0);
                console.log(type);
                console.log(buf.readInt8(0));

		//mClientID
                buf.writeInt8(socket.mClientID,1);
                console.log(socket.mClientID);
                console.log(buf.readInt8(1));


                server.send(buf, 0, buf.length, mServerPort, mServerIP, function(err, bytes)
                {
                });
        });

        socket.on('send_quit_game', function(message,remote)
	{
                //send to c++ server
                var buf = new Buffer(2);

		//type
                type = -118;
                buf.writeInt8(type,0);
                console.log(type);
                console.log(buf.readInt8(0));

		//mClientID
                buf.writeInt8(socket.mClientID,1);
                console.log(socket.mClientID);
                console.log(buf.readInt8(1));

		console.log('mClientID:' + socket.mClientID + ' disconnecting');

                server.send(buf, 0, buf.length, mServerPort, mServerIP, function(err, bytes)
                {
                });

        });

        socket.on('send_move', function(message,remote)
        {
                mMessage = message;
		var messageArray = message.split(" ");

		var currentKey = parseInt(messageArray[1]);	               
		type = 2;

                //send to c++ server
                var buf = new Buffer(3);
                buf.writeInt8(type,0);
                buf.writeInt8(socket.mClientID,1);
                buf.writeInt8(currentKey,2);

                server.send(buf, 0, buf.length, mServerPort, mServerIP, function(err, bytes)
                {
                });
        });

	
        socket.on('send_login', function(message,remote)
        {
		var messageLength = message.length;
		var blankSpot = 0;	
	
		for (i = 0; i < messageLength; i++)
		{
			if (message[i] == ' ')	
			{
				console.log('message:' + i + ' is null'); 
				blankSpot = i;
			}
		}


                //send to c++ server
	
		//buf
                var bufLength = parseInt(3 + messageLength); // 4 items minus blankspot + messageLength
                var buf = new Buffer(bufLength);

		//type
                type = -125;
                buf.writeInt8(type,0);
                console.log(type);
                console.log(buf.readInt8(0));

		//mClientID
                buf.writeInt8(socket.mClientID,1);
                console.log(socket.mClientID);
                console.log(buf.readInt8(1));

		//usernameLength
		var usernameLength = parseInt(blankSpot);
                buf.writeInt8(usernameLength,2);
                console.log(usernameLength);
                console.log(buf.readInt8(2));

		//passwordLength
		var passwordLength = parseInt(messageLength - blankSpot - 1);
                buf.writeInt8(passwordLength,3);
                console.log(passwordLength);
                console.log(buf.readInt8(3));


		for (u = 0; u < usernameLength; u++)
		{
			console.log(message[parseInt(u)].charCodeAt(0));
  			buf.writeInt8(message[u].charCodeAt(0),parseInt(u + 4));
		}

		for (p = 0; p < passwordLength; p++)
		{
			console.log(message[parseInt(p + blankSpot + 1)].charCodeAt(0));
  			buf.writeInt8(message[parseInt(p + blankSpot + 1)].charCodeAt(0),parseInt(usernameLength + 4 + p));
		}

		
                server.send(buf, 0, buf.length, mServerPort, mServerIP, function(err, bytes)
                {
                });

		
        });
});

server.on("message", function (msg, rinfo)
{
	//to break out of message when it's over
	var length = msg.length;
	var count = 0;

        var type   = msg.readInt8(0);
	count++
       
        //add shape
	//this is getting called 2 times for some reason
        if (type == -103)
        { 
                var clientID = msg.readInt8(1);
                var client   = msg.readInt8(2);
                var index    = msg.readInt8(3);
                var xpos     = msg.readFloatLE(4);
                var ypos     = msg.readFloatLE(8);
                var zpos     = msg.readFloatLE(12);
                var xrot     = msg.readFloatLE(16);
                var zrot     = msg.readFloatLE(20);
                var mesh     = msg.readInt8(24);
                var anim     = msg.readInt8(25);
        
                //let's just pass off data msg to browsers
		var addShapeString = type;

                addShapeString = addShapeString + "," + client + "," + index + "," + xpos + "," + ypos + "," + zpos + "," + xrot + "," + zrot + "," + mesh + "," + anim; 

		io.sockets.clients().forEach(function (socket)
		{
			if (socket.mClientID == clientID)
			{
		//		console.log('addShape-sendToBrowser: ' + clientID + 'message:' + addShapeString);
       				socket.emit('news', addShapeString)
			} 
		});
        }

	
        if (type == -114)
	{
		console.log('udp logout');
		socket.emit('news','-114');
	}

        if (type == -113)
	{
                var clientID = msg.readInt8(1);
		var loginString = type;
		loginString = loginString + "," + clientID; 

		io.sockets.clients().forEach(function (socket)
		{
			if (socket.mClientID == clientID)
			{
       				socket.emit('news', loginString)
			} 
		});
	}

	//mMessageRemoveShape
	if (type == -104)
	{
 		var clientID = msg.readInt8(1);
 		var index    = msg.readInt8(1);
                var removeShapeString = type;
                removeShapeString = removeShapeString + "," + clientID + "," + index;

                io.sockets.clients().forEach(function (socket)
                {
                        if (socket.mClientID == clientID)
                        {
                                socket.emit('news', removeShapeString)
                        }
                });
	}

/*
        if (type == -109)
        {
		console.log('1999999');
                var clientID = msg.readInt8(1);
                var length = msg.readInt8(1);
                var string = type;
		string = string + "," + length;

 		for (i = 0; i < length; i++)
                {
                        //buf.writeInt8(message[u].charCodeAt(0),i+);
			string = "," + msg.readInt8(1);	
                }


                io.sockets.clients().forEach(function (socket)
                {
                        if (socket.mClientID == clientID)
                        {
				console.log('emitting 109');
                                socket.emit('news', string)
                        }
                });
        }
*/
        if (type == -109)
        {
                var clientID = msg.readInt8(1);
                var string = type;
                string = string + "," + clientID;

                io.sockets.clients().forEach(function (socket)
                {
                        if (socket.mClientID == clientID)
                        {
                                socket.emit('news', string)
                        }
                });
        }


        if (type == -99)
	{
                var clientID = msg.readInt8(1);
		var loginString = type;
		loginString = loginString + "," + clientID; 

		io.sockets.clients().forEach(function (socket)
		{
			if (socket.mClientID == clientID)
			{
       				socket.emit('news', loginString)
			} 
		});
	}


	if (type == 1)
	{
		skipCounter++;
	
		var dataString = type;
	
		//sequence
        	dataString = dataString + "," + msg.readUInt16LE(count);
		count = count + 2;


		if (skipCounter > fireNumber)
		{

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
		
			} //  end while count < length
		
	
			//console.log('clients in room: ' + io.sockets.clients('game1'));
			//console.log('rooms: ' + io.sockets.manager.rooms);
	
//			io.sockets.in('game1').emit('news',dataString)	
			
		       	io.sockets.clients().forEach(function (socket)
                        {
				if (socket.mClientID > 0)
				{
                       			socket.emit('news', dataString)
				}
                        });

			//io.sockets.emit('news', dataString)
			skipCounter = 0;

		} //end skip check	
	} //if type
});

server.on("listening", function ()
{
        var address = server.address();
        console.log("server listening " +
        address.address + ":" + address.port);
});

server.bind(41234);

//send initial connection to c++ server
//send to c++ server
var buf = new Buffer(1);
buf.writeInt8(-121,0);
server.send(buf, 0, buf.length, mServerPort, mServerIP, function(err, bytes)
{
	console.log('sent connect from node');
});
