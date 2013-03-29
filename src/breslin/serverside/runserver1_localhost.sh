./build.sh
pkill Server
./../vserver/dist/bin/Server 1 &
node ../../udp_server_localhost.js 
