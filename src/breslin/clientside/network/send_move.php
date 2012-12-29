<?php
//grab buffer
$messageFrame = $_POST["messageFrame"];
$outgoingSequence = $_POST["outgoingSequence"];
$flags = $_POST["flags"];
$keyCurrent = $_POST["keyCurrent"];



//have to create this every time because it cannot be save in a session variable as it's a resource
$sock = socket_create(AF_INET, SOCK_DGRAM,0);

$packed = pack("c",$messageFrame); //signed integer
$packed .= pack("s",$outgoingSequence); //signed short mOutgoingSequence
$packed .= pack("c",$flags); //signed integer
$packed .= pack("c",$keyCurrent); //signed integer

$len = strlen($packed);

socket_sendto($sock, $packed, $len, 0, '192.168.1.100', 30004);
socket_close($sock);
//echo $outgoingSequence;
echo $packed;

?>

