import processing.core.*; 
import processing.data.*; 
import processing.event.*; 
import processing.opengl.*; 

import http.requests.*; 
import processing.sound.*; 

import java.util.HashMap; 
import java.util.ArrayList; 
import java.io.File; 
import java.io.BufferedReader; 
import java.io.PrintWriter; 
import java.io.InputStream; 
import java.io.OutputStream; 
import java.io.IOException; 

public class MotionSensorClient extends PApplet {




boolean motion = false;
SoundFile soundFile;

public void setup() {
	
	soundFile = new SoundFile(this, "alarm.mp3");
	thread("backgroundRequest");
}

public void draw() {
	if (motion) {
		background(255, 0, 0);
	}
	else background(0);
}

public void backgroundRequest() {
	while (true) {
		GetRequest get = new GetRequest("http://192.168.1.50");
		get.send();
		String response = trim(get.getContent());
		if (response.equals("MOTION")) {
			motion = true;
			soundFile.play();
		}
		else motion = false;
		delay(1000);
	}
}
  public void settings() { 	size(200,200); }
  static public void main(String[] passedArgs) {
    String[] appletArgs = new String[] { "MotionSensorClient" };
    if (passedArgs != null) {
      PApplet.main(concat(appletArgs, passedArgs));
    } else {
      PApplet.main(appletArgs);
    }
  }
}
