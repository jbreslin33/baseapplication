<?php
$bytebuffer = $_POST["bytebuffer"];

//is this where you want to send back server data from game? or should we use seperate ajax calls? 
//scratch that for a minute i think you need to interject here and..
//ask if this is a mMessageConnect and if so
//then ask the db for a client_id
//then send back the client_id...
//and tell db that you got it.

$client_id = 0;

if ($bytebuffer == -111)
{
	//get current client id then update record 
	$conn = pg_connect("host=localhost dbname=abcandyou user=postgres password=mibesfat")
        or die('Could not connect: ' . pg_last_error());

	$query = "select client_id from client where id = 1;";

	$result = pg_query($conn,$query);
 	$row = pg_fetch_array($result, 0);
	
	//echo $row["client_id"];
	$client_id = $row["client_id"];

	//now update the record
	$new_client_id = $client_id + 1;
	$query = "update client set client_id = ";
	$query .= $new_client_id;
	$query .= " where id = 1";	

	$result = pg_query($conn,$query);
	echo $client_id;
}
else if ($bytebuffer == 1)
{
	echo 'should send data'; 
}
else 
{
	echo $bytebuffer;
	echo 'something else';
}

//have to create this every time because it cannot be save in a session variable as it's a resource
$sock = socket_create(AF_INET, SOCK_DGRAM,0);

$packed = pack("i",$bytebuffer);
$len = strlen($packed);

socket_sendto($sock, $packed, $len, 0, '192.168.1.100', 30004);
socket_close($sock);


?>

