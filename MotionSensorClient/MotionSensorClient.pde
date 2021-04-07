import http.requests.*;
import processing.sound.*;
import java.net.*;
import java.io.*;
import java.nio.charset.*;

boolean motion = false;
SoundFile soundFile;

public void setup() {
	size(200,200);
	soundFile = new SoundFile(this, "alarm.mp3");
	try {
		thread("backgroundRequest");
	} catch (Exception e) {
		print ("got an exception\n");
	}
}

public void draw() {
	if (motion) {
		background(255, 0, 0);
	}
	else background(0);
}

public void backgroundRequest() {
	
	try {
		while (true) {
			try {
				URL url = new URL("http://192.168.1.50/");
				HttpURLConnection http = (HttpURLConnection) url.openConnection();
				http.setConnectTimeout(1000);
				http.setReadTimeout(1000);
				http.setRequestMethod("GET");
				InputStream in = new BufferedInputStream(http.getInputStream());
				String response = trim(IOUtils.toString(in, StandardCharsets.UTF_8));
				print("response is " + response + "\n");
				if (response.equals("MOTION")) {
					motion = true;
					soundFile.play();
				}
				else motion = false;
			} catch (Exception e) {
				print("Unable to connect: " + e.getCause() + "\n");
			}

			delay(1000);
		}
	} catch (Exception e) {
		print ("This is only here because url requires a try/catch\n");
	}
}
