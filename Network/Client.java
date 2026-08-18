
import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.net.Socket;


public class Client {
    public static void main(String[] args) throws Exception {
        Socket s = new Socket("localhost", 5000);
        System.out.println("Connected to server");

        BufferedReader in = new BufferedReader(new InputStreamReader(s.getInputStream()));
        BufferedReader kb = new BufferedReader(new InputStreamReader(System.in));

        new Thread(() -> {
            try {
                String msg;
                while ((msg = in.readLine()) != null)
                    System.out.println("Server: " + msg);
            } catch (Exception e) {}
        }).start();

        String msg;
        while ((msg = kb.readLine()) != null){
            System.out.println(msg);
        }
    }
}