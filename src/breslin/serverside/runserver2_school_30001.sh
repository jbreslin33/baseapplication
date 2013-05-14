./build.sh
pkill Server
./../vserver/dist/bin/Server 2 30001 &
node ../../udp_server_school_30001.js 
