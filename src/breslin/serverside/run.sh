./build.sh
pkill Server
./../vserver/dist/bin/Server $1 $2 &
node ../../udp_server_localhost_30001.js 
