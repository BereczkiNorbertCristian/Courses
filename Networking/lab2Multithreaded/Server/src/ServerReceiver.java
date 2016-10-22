import java.io.IOException;
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.InetAddress;
import java.net.SocketException;

/**
 * Created by bnorbert on 22.10.2016.
 * bnorbertcristian@gmail.com
 */
public class ServerReceiver implements Runnable {

    InetAddress clientIPAdress;
    int clientPort;
    byte[] bufferReceiver;
    DatagramSocket serverSocket;

    public ServerReceiver(InetAddress IPAdress, int clientPort, DatagramSocket serverSocket){

        this.clientIPAdress=IPAdress;
        this.clientPort=clientPort;
        bufferReceiver =new byte[1024];
        this.serverSocket=serverSocket;

    }

    @Override
    public void run(){

        try {
            while (true) {

                DatagramPacket receivedPacket = new DatagramPacket(bufferReceiver, bufferReceiver.length);

                serverSocket.receive(receivedPacket);
                String sentence=new StringNetworkWrapper(new String(receivedPacket.getData())).getString();
                System.out.println("Received: "+sentence);

            }
        }
        catch (SocketException e) {System.out.println("Socket: "+e.getMessage());}
        catch (IOException e) {System.out.println("IO: " + e.getMessage());}
        finally {
            if(serverSocket!=null){
                serverSocket.close();
            }
        }

    }
}
