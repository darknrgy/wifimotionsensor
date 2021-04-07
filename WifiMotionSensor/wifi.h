#include <WiFi.h>
#include "password.h"

WiFiServer server(80);

void setupwifi() {
	Serial.print("Connecting to ");
    Serial.println(ssid);

    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }

    Serial.println("");
    Serial.println("WiFi connected.");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
    
    server.begin();
}

bool pollwifi(bool motion) {
	static unsigned long counter = 0;
	
	WiFiClient client = server.available();
	  if (client) {
		String currentLine = "";
		counter ++;
		while (client.connected()) {
			if (client.available()) {
				char c = client.read();
				if (c == '\n') {
					if (currentLine.length() == 0) {
						client.println("HTTP/1.1 200 OK");
						client.println("Content-type:text/html");
						client.println();
						if (motion) client.println("MOTION");
						else client.println("CLEAR ");
						client.println();
						return false;
					} else {
						currentLine = "";
					}
				} else if (c != '\r') {
					currentLine += c;
				}

				if (currentLine.endsWith("GET /")) {
			  		currentLine = "";
				}
			}
		}
		// close the connection:
		client.stop();
  	}

  	return motion;
}
