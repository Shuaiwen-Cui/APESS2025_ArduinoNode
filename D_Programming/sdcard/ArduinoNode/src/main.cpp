#include <Arduino.h>

#include <SPI.h>
#include <SD.h>

const int chipSelect = 10; // Chip Select (CS) pin for SD card module

void setup() {
  Serial.begin(9600);
  while (!Serial);  // Wait for Serial Monitor to open

  Serial.println("Initializing SD card...");

  if (!SD.begin(chipSelect)) {
    Serial.println("SD card initialization failed!");
    while (1); // Halt
  }

  Serial.println("SD card initialized.");

  // Write to file
  File dataFile = SD.open("test.txt", FILE_WRITE);
  if (dataFile) {
    dataFile.println("Hello from Arduino UNO R4 WiFi!");
    dataFile.close();
    Serial.println("Data written to test.txt");
  } else {
    Serial.println("Failed to open file for writing.");
  }

  // Read from file
  dataFile = SD.open("test.txt");
  if (dataFile) {
    Serial.println("Reading from test.txt:");
    while (dataFile.available()) {
      Serial.write(dataFile.read());
    }
    dataFile.close();
  } else {
    Serial.println("Failed to open file for reading.");
  }
}

void loop() {
  // Nothing here
}
