import java.io.*;
import java.net.*;



public class Server{
    public static void main(String[] args) throws Exception {
        ServerSocket ss = new ServerSocket(5000);

        System.out.println("Waiting");
        
        Socket s = ss.accept();

        BufferedReader in = new BufferedReader(new InputStreamReader(s.getInputStream()));


        BufferedReader kb = new BufferedReader(new InputStreamReader(System.in));

        new Thread(()->{
            try {
                String msg;
                while((msg = in.readLine()) != null){
                    System.out.println(msg);
                }
            } catch (Exception e) {
            }
        }).start();

        String msg;
        while((msg = kb.readLine()) != null){
            System.out.println(msg);
        }

    }
}