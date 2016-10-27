import javax.xml.crypto.Data;
import java.io.IOException;
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.InetAddress;
import java.net.SocketException;

/**
 * Created by bnorbert on 26.10.2016.
 * bnorbertcristian@gmail.com
 */
public class ServerSender implements Runnable {

    int clientPort;
    byte[] bufferSender;
    DatagramSocket inUseSocket;
    byte[] bufferReceiver;
    InetAddress clientIPAdress;

    public ServerSender(int newPort, int oldPort, InetAddress clientAdress,DatagramSocket oldSocket) throws Exception{

        inUseSocket=new DatagramSocket(newPort);
        this.clientPort=oldPort;
        bufferSender=new byte[1024];
        bufferReceiver=new byte[1024];
        clientIPAdress=clientAdress;
        bufferSender=Integer.toString(newPort).getBytes();
        DatagramPacket sendPacket= new DatagramPacket(bufferSender,bufferSender.length,clientAdress,oldPort);
        oldSocket.send(sendPacket);

    }

    @Override
    public void run(){

        try{
            DatagramPacket receivedPacket= new DatagramPacket(bufferReceiver,bufferReceiver.length);

            inUseSocket.receive(receivedPacket);
            String firstNumber= new StringNetworkWrapper(new String(receivedPacket.getData())).getString();
            inUseSocket.receive(receivedPacket);
            String secondNumber=new StringNetworkWrapper(new String(receivedPacket.getData())).getString();

            int ret=Integer.parseInt(firstNumber) + Integer.parseInt(secondNumber);

            bufferSender=new String(Integer.toString(ret)).getBytes();

            DatagramPacket sendPacket=new DatagramPacket(bufferSender,bufferSender.length,clientIPAdress,clientPort);

            inUseSocket.send(sendPacket);

        }
        catch (SocketException e){
            System.out.println("Socket: " + e.getMessage());
        }
        catch (IOException e){
            System.out.println("IO: " + e.getMessage());
        }
        finally {
            if(inUseSocket!=null){
                inUseSocket.close();
            }
        }



    }

}
