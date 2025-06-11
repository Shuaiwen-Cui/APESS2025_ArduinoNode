#include <Arduino.h>

#include <SPI.h>
#include <RF24.h>

RF24 radio(9, 8);  // CE on D9, CSN on D8

const byte address[6] = "NODE1";

unsigned long counter = 1;  // Message counter

void setup() {
  Serial.begin(9600);
  radio.begin();
  radio.setPALevel(RF24_PA_LOW);
  radio.setChannel(108);
  radio.openWritingPipe(address);
  radio.stopListening();
}

void loop() {
  char msg[32];
  snprintf(msg, sizeof(msg), "%lu", counter);  // Convert number to string

  bool success = radio.write(&msg, sizeof(msg));

  Serial.print("Sending: ");
  Serial.print(msg);
  Serial.println(success ? " [OK]" : " [Failed]");

  counter++;
  delay(1000);
}
