<?php

$bytebuffer = $_POST["bytebuffer"];

$sock = socket_create(AF_INET, SOCK_DGRAM,0);

$packed = pack("i",$bytebuffer);
$len = strlen($packed);

socket_sendto($sock, $packed, $len, 0, '192.168.1.100', 30004);
socket_close($sock);
echo $bytebuffer;

?>

