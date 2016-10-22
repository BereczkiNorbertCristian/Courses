import java.io.IOException;
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.InetAddress;
import java.net.SocketException;
import java.util.Scanner;

/**
 * Created by bnorbert on 22.10.2016.
 * bnorbertcristian@gmail.com
 */
public class ServerSender implements Runnable {

    InetAddress clientIPAdress;
    int clientPort;
    DatagramSocket serverSocket;
    byte[] bufferSender;
    Scanner scanner;

    public ServerSender(InetAddress clientIPAdress,int clientPort,DatagramSocket serverSocket){
        this.bufferSender =new byte[1024];
        this.clientIPAdress=clientIPAdress;
        this.serverSocket=serverSocket;
        this.clientPort=clientPort;
        scanner=new Scanner(System.in);
    }

    @Override
    public void run(){

        try{


            while(true) {
                System.out.println("Reply back:");

                String message = scanner.nextLine();
                bufferSender = message.getBytes();
                DatagramPacket sendPacket = new DatagramPacket(bufferSender, bufferSender.length, clientIPAdress, clientPort);
                serverSocket.send(sendPacket);
            }

        }
        catch (SocketException e) {
            System.out.println("Socket: " + e.getMessage());
        }
        catch (IOException e){
            System.out.println("IO: " + e.getMessage());
        }
        finally {
            if(serverSocket != null){
                serverSocket.close();
            }
        }

    }


}
