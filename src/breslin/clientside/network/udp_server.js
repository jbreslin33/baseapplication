var PORT = 33333;
var HOST = '192.168.1.101';

var dgram = require('dgram');
var server = dgram.createSocket('udp4');

server.on('listening', function () {
    var address = server.address();
    console.log('UDP Server listening on ' + address.address + ":" + address.port);
});

server.on('message', function (message, remote) {
    console.log(remote.address + ':' + remote.port +' - ' + message);

});

server.bind(PORT, HOST);

//send connect
var buf = new Buffer(1);
buf.writeInt8(-101,0);

server.send(buf, 0, buf.length, 30004, HOST, function(err, bytes) {
  //client.close();
});

