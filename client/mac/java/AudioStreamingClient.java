import javax.sound.sampled.*;
import java.io.InputStream;
import java.net.Socket;

public class AudioStreamingClient {
    public static void main(String[] args) {
        String serverAddress = "192.168.1.2"; // Replace with the server's IP address
        int port = 5000; // Port for streaming audio
        AudioFormat format = new AudioFormat(48000, 16, 2, true, true); // Stereo, 16-bit, 44.1kHz

        try (Socket socket = new Socket(serverAddress, port);
             InputStream inputStream = socket.getInputStream();
             SourceDataLine sourceLine = AudioSystem.getSourceDataLine(format)) {

            sourceLine.open(format);
            sourceLine.start();

            byte[] buffer = new byte[4096]; // Buffer for received audio data
            int bytesRead;

            System.out.println("Receiving and playing audio from server...");

            while ((bytesRead = inputStream.read(buffer)) != -1) {
                sourceLine.write(buffer, 0, bytesRead); // Play received audio
            }
        } catch (Exception e) {
            System.out.println("Error receiving audio: " + e.getMessage());
        }
    }
}
