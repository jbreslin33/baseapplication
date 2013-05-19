./build.sh
pkill Server
./../vserver/dist/bin/Server $1 $2 &
if test $3 -eq 1
then
node ../../udp.js 127.0.0.1 $2 10001 main_localhost_30001.html 40001 
fi


