import javax.sound.sampled.*;
import java.io.*;
import java.net.*;

public class AudioServer {
    public static void main(String args[]) {
        try {
            someFunction();
            // Set up the server to listen on a port
            ServerSocket serverSocket = new ServerSocket(5000);
            System.out.println("Server is listening on port 5000...");

            // Accept client connections
            Socket clientSocket = serverSocket.accept();
            System.out.println("Client connected!");

            // Set up the audio capture (same as before)
            Mixer mixer = null;
            Mixer.Info[] mixers = AudioSystem.getMixerInfo();
            for (Mixer.Info mixerInfo : mixers) {
                if (mixerInfo.getName().equals("BlackHole 2ch")) {
                    mixer = AudioSystem.getMixer(mixerInfo);
                    break;
                }
            }
            Line.Info[] lineInfos = mixer.getTargetLineInfo();
            TargetDataLine line = (TargetDataLine) mixer.getLine(lineInfos[0]);
            line.open();
            line.start();

            // Set up streams for communication with the client
            OutputStream out = clientSocket.getOutputStream();
            byte[] buffer = new byte[4096];
            
            while (true) {
                int bytesRead = line.read(buffer, 0, buffer.length);
                System.out.println(buffer);
                out.write(buffer, 0, bytesRead);  // Stream captured audio to the client
                out.flush();
            }
            
        } catch (IOException | LineUnavailableException e) {
            e.printStackTrace();
        }
    }
}