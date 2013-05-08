./build.sh
pkill Server
./../vserver/dist/bin/Server 2 30002 &
node ../../udp_server_localhost_30002.js 
