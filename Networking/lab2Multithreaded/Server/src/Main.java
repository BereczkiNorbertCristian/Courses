import javax.xml.crypto.Data;
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.Inet4Address;
import java.net.InetAddress;

/**
 * Created by bnorbert on 20.10.2016.
 */


public class Main {

    public static void main(String[] args) throws Exception {

        DatagramSocket serverSocket=new DatagramSocket(4444);
        byte[] buffer=new byte[1024];

        DatagramPacket receivedPacket = new DatagramPacket(buffer,buffer.length);
        serverSocket.receive(receivedPacket);

        String received=new StringNetworkWrapper(new String(receivedPacket.getData())).getString();
        System.out.println("RECEIVED:"+received);
        InetAddress IPAdress=receivedPacket.getAddress();
        int senderPort=receivedPacket.getPort();


        Thread receiver=new Thread(new ServerReceiver(IPAdress,senderPort,serverSocket));
        Thread sender=new Thread(new ServerSender(IPAdress,senderPort,serverSocket));

        receiver.start();
        sender.start();

        while(true){
            continue;
        }

    }


}
