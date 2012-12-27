<?php
        $sock = socket_create(AF_INET, SOCK_DGRAM,0);
        $_SESSION["sock"] = $sock;

        $msg = -101;
        $packed = pack("i",$msg);
        $len = strlen($packed);

        socket_sendto($sock, $packed, $len, 0, '192.168.1.100', 30004);
?>

