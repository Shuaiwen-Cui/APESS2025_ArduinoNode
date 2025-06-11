#include <Arduino.h>
#include <WiFiS3.h>

char ssid[] = "CSW@CEE";     // your network SSID (name)
char pass[] = "88888888";        // your network password

void setup() {
  Serial.begin(9600);
  while (!Serial);  // wait for serial monitor

  Serial.println("Attempting to connect to WiFi...");

  while (WiFi.begin(ssid, pass) != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }

  Serial.println("\nConnected to WiFi!");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  // Your main code here, possibly using WiFi features
}
