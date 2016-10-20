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
        byte[] receivedData=new byte[1024];
        byte[] sendData=new byte[1024];


        while(true) {
            DatagramPacket receivedPacket = new DatagramPacket(receivedData, receivedData.length);
            serverSocket.receive(receivedPacket);

            String sentence = new String(receivedPacket.getData());
            StringNetworkWrapper stringNetworkWrapper = new StringNetworkWrapper(sentence);
            String received = stringNetworkWrapper.getString();
            System.out.println("RECEIVED:" + received);

            InetAddress IPAdress = receivedPacket.getAddress();
            int senderPort = receivedPacket.getPort();
            String capitalizedSentence = received.toUpperCase();
            sendData = capitalizedSentence.getBytes();
            DatagramPacket sendPacket =
                    new DatagramPacket(sendData, sendData.length, IPAdress, senderPort);
            serverSocket.send(sendPacket);
        }


    }


}
