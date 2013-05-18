./build.sh
pkill Server
./../vserver/dist/bin/Server $1 $2 &
if test $3 -eq 1
then
node ../../udp_server_localhost_30001.js 
fi


