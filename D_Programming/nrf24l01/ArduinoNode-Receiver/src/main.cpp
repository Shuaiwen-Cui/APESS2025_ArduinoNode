#include <Arduino.h>

#include <SPI.h>
#include <RF24.h>

RF24 radio(9, 8);  // CE on D9, CSN on D8

const byte address[6] = "NODE1";

void setup() {
  Serial.begin(9600);
  radio.begin();
  radio.setPALevel(RF24_PA_LOW);
  radio.setChannel(108);
  radio.openReadingPipe(0, address);
  radio.startListening();
}

void loop() {
  if (radio.available()) {
    char buffer[32] = {0};
    radio.read(&buffer, sizeof(buffer));

    Serial.print("Received: ");
    Serial.println(buffer);
  }
}
