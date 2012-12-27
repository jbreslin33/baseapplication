var Network = new Class(
{

initialize: function(application,serverIP, serverPort)
{
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
},

//this should call ajax function on server to send
send: function(b)
{
	this.log('send before xmlHttprequest');
	var xmlhttp;
if (window.XMLHttpRequest)
  {// code for IE7+, Firefox, Chrome, Opera, Safari
  xmlhttp=new XMLHttpRequest();
  }
else
  {// code for IE6, IE5
  xmlhttp=new ActiveXObject("Microsoft.XMLHTTP");
  }
xmlhttp.onreadystatechange=function()
  {
  if (xmlhttp.readyState==4 && xmlhttp.status==200)
    {
    document.getElementById("demo").innerHTML=xmlhttp.responseText;
    }
  }
xmlhttp.open("POST","/breslin/clientside/network/ajax_info.txt",true);
xmlhttp.send();

}

});

