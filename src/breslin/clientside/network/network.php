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

//	this.mSocket.emit('message', 33);

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
	return io.connect('192.168.1.101:10000');
	
},

//this should call ajax function on server to send
/*
sendConnect: function()
{
        var xmlhttp;
        if (window.XMLHttpRequest)
        {
                xmlhttp=new XMLHttpRequest();
        }
        else
        {
                xmlhttp=new ActiveXObject("Microsoft.XMLHTTP");
        }
        xmlhttp.onreadystatechange=function()
        {
                if (xmlhttp.readyState==4 && xmlhttp.status==200)
                {
                        document.getElementById("mClientID").innerHTML=xmlhttp.responseText;
		}
        }
        xmlhttp.open("POST","/breslin/clientside/network/send_connect.php",true);
        xmlhttp.send();
},
*/
sendConnect: function()
{
	this.mSocket.emit('browser_message', '-101');
},
/*
 	this.mSocket.on('news', function (data)
	{
    		console.log(data);
    		socket.emit('my other event', { my: 'data' });
  	});
*/
// send the move that is new 
sendMove: function(messageFrame,outgoingSequence,flags,keyCurrent)
{
	//temp fix because i am having trouble setting vars in readystate above
	if (this.mClientID == 0)
	{
 		this.mClientID = document.getElementById("mClientID").innerHTML;
	}
        
	var xmlhttp;
        if (window.XMLHttpRequest)
        {
                xmlhttp=new XMLHttpRequest();
        }
        else
        {
                xmlhttp=new ActiveXObject("Microsoft.XMLHTTP");
        }
        
	xmlhttp.open("POST","/breslin/clientside/network/send_move.php",true);
        xmlhttp.setRequestHeader("Content-type","application/x-www-form-urlencoded");
        xmlhttp.send("messageframe=" + messageFrame + "&clientid=" + this.mClientID + "&outgoingsequence=" + outgoingSequence + "&flags=" + flags + "&keycurrent=" + keyCurrent);

},

checkForByteBuffer: function()
{
	var xmlhttp;
        if (window.XMLHttpRequest)
        {
                xmlhttp=new XMLHttpRequest();
        }
        else
        {
                xmlhttp=new ActiveXObject("Microsoft.XMLHTTP");
        }
        xmlhttp.onreadystatechange=function()
        {
                if (xmlhttp.readyState==4 && xmlhttp.status==200)
                {
                        document.getElementById("mByteBuffer").innerHTML=xmlhttp.responseText;
                }
        }
        xmlhttp.open("POST","/breslin/clientside/network/check_for_byte_buffer.php",true);
        xmlhttp.setRequestHeader("Content-type","application/x-www-form-urlencoded");
        xmlhttp.send();
},

getAllShapes: function()
{
	var xmlhttp;
        if (window.XMLHttpRequest)
        {
                xmlhttp=new XMLHttpRequest();
        }
        else
        {
                xmlhttp=new ActiveXObject("Microsoft.XMLHTTP");
        }
        xmlhttp.onreadystatechange=function()
        {
                if (xmlhttp.readyState==4 && xmlhttp.status==200)
                {
                        document.getElementById("mByteBuffer").innerHTML=xmlhttp.responseText;
                }
        }
        xmlhttp.open("POST","/breslin/clientside/network/get_all_shapes.php",true);
        xmlhttp.setRequestHeader("Content-type","application/x-www-form-urlencoded");
        xmlhttp.send();
}


});

