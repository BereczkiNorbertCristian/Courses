import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.util.LinkedList;
import java.util.List;

/**
 * Created by bnorbert on 26.10.2016.
 * bnorbertcristian@gmail.com
 */
public class Main {

    public static void main(String[] args) throws Exception {


        final int portFixed=5454;
        int counter=0;

        DatagramSocket serverSocket=new DatagramSocket(portFixed);

        byte[] buffer=new byte[1024];


        DatagramPacket receivedPacket = new DatagramPacket(buffer,buffer.length);
        List<Thread> threadList=new LinkedList<Thread>();
        int currIdx=0;
        while(true){

            serverSocket.receive(receivedPacket);

            String msg=new StringNetworkWrapper(new String(receivedPacket.getData())).getString();
            System.out.println(msg);

            counter++;
            threadList.add(new Thread(new ServerSender(portFixed+counter,receivedPacket.getPort(),receivedPacket.getAddress(),serverSocket)));
            threadList.get(currIdx).start();
            currIdx++;

        }


    }


}
