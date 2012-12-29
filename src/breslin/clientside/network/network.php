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
	//this.log('open socket on server');
},

//this should call ajax function on server to send
sendConnect: function()
{
        var xmlhttp;
        if (window.XMLHttpRequest)
        {
                // code for IE7+, Firefox, Chrome, Opera, Safari
                xmlhttp=new XMLHttpRequest();
        }
        else
        {
                // code for IE6, IE5
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
                // code for IE7+, Firefox, Chrome, Opera, Safari
                xmlhttp=new XMLHttpRequest();
        }
        else
        {
                // code for IE6, IE5
                xmlhttp=new ActiveXObject("Microsoft.XMLHTTP");
        }
        xmlhttp.onreadystatechange=function()
        {
/*
                if (xmlhttp.readyState==4 && xmlhttp.status==200)
                {
                        document.getElementById("mMessageFrame").innerHTML=xmlhttp.responseText;
                }
*/
        }
        xmlhttp.open("POST","/breslin/clientside/network/send_move.php",true);
        xmlhttp.setRequestHeader("Content-type","application/x-www-form-urlencoded");
        xmlhttp.send("messageframe=" + messageFrame + "&clientid=" + this.mClientID + "&outgoingsequence=" + outgoingSequence + "&flags=" + flags + "&keycurrent=" + keyCurrent);

}


});

