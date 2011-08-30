import java.io.IOException;
import java.net.DatagramSocket;
import java.net.InetSocketAddress;
import java.net.SocketAddress;
import java.nio.ByteBuffer;
import java.nio.ByteOrder;
import java.nio.channels.DatagramChannel;

public class UDPTimeServer {

  public final static int DEFAULT_PORT = 37;

  public static void main(String[] args) throws IOException {

    int port = 37;

    ByteBuffer in = ByteBuffer.allocate(1400);
    SocketAddress address = new InetSocketAddress(port);
    DatagramChannel channel = DatagramChannel.open();
    channel.configureBlocking(false);

    DatagramSocket socket = channel.socket();

    socket.bind(address);

    System.err.println("bound to " + address);

    while (true) {
      try {
        in.clear();
        SocketAddress client = channel.receive(in);
        System.out.println("hhh");
        //System.err.println(client);


      } catch (Exception ex) {
        System.err.println(ex);
      }
    }
  }
}