./build.sh
pkill Server
./../vserver/dist/bin/Server 2 &
node ../../udp_server_localhost.js 
