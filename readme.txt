set permissions of /upload file or it won't work:
sudo chmod -R 777 web/insert/upload

to compile:

cd src/breslin/vserver
cmake .
sudo make install

cd src/breslin/vclient
cmake .
sudo make install

cd src
yes | sudo ./setup.sh


then:
you must edit path.js 
sudo vi node/lib/path.js +360
comment out line 360
it will complain about strings if not.... 

sudo vi node_modules/socket.io/node_modules/socket.io-client/lib/socket.js +37
change to : 
var conn_options = {
  'sync disconnect on unload':false
};

./compile.sh



then run:
yes | sudo ./setup.sh


run:
cd /src/breslin/serverside
./runserver1.sh
