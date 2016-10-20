<?php
$s=socket_create(AF_INET,SOCK_DGRAM,0);
echo $s;
$b=socket_bind($s,"127.0.0.1",8888);
echo $b.'\n';
while(1){
$a=socket_listen($s);
echo $a;
socket_recvfrom($s,$buf,100,0,$rip,$rp);
echo "received ".$buf."from ".$rip.$rp;
}
?>
