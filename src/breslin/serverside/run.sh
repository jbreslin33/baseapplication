./build.sh
pkill Server
./../vserver/dist/bin/Server $1 $2 &

if test $3 -eq 1
then
node ../../udp.js 127.0.0.1 $2 10001 main_localhost.html 40001 
fi

if test $3 -eq 2 
then
node ../../udp.js 127.0.0.1 $2 10001 main_115.html 40001 
fi

if test $3 -eq 3 
then
node ../../udp.js 192.168.2.88 $2 10001 main_88.html 40001 
fi