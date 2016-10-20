<?php
$s=socket_create(AF_INET,SOCK_DGRAM,0);
socket_sendto($s,"hello",5,0,"localhost",1234);
?>
