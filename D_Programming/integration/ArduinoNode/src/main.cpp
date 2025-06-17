/* ARDUINO IOT WIRELESS SENSOR NODE */

/* DEPENDENCIES */
// Arduino Framework
#include <Arduino.h>

// WiFi Communication
#include <WiFiS3.h>

// Network Time Protocol (NTP)
#include <WiFiUdp.h>
#include <NTPClient.h>

// I2C Communication
#include <Wire.h>

// SPI Communication
#include <SPI.h>

// MPU6050 Library
#include <MPU6050.h>

// RGB LED
#include <FastLED.h>

// SD Card
#include <SD.h>

// Radio Frequency (RF) Communication
#include <RF24.h>

/* CONFIGURATIONS */

/* MACROS */
// LED
#define NUM_LEDS 4
#define LED_PIN 7

// Touch Sensor
#define TOUCH_SENSOR_PIN 3 // Pin for touch sensor

// SD Card
#define SD_CS_PIN 10 // Chip Select pin for SD card module

// RF MODE
// #define RF_MODE_TRANSMITTER // Change to RF_MODE_RECEIVER for receiver mode
#define RF_MODE_RECEIVER // Uncomment for receiver mode

/* HELPER VARIABLES AND FUNCTIONS */

// WiFi Credentials
// char ssid[] = "Shaun's Iphone";     // your network SSID (name)
// char pass[] = "cshw0918";        // your network password
char ssid[] = "CSW@CEE";  // your network SSID (name)
char pass[] = "88888888"; // your network password

// NTP
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org", 8 * 3600, 60000); // UTC+8

// Structure to hold date and time components
struct DateTimeStruct
{
  int year;
  int month;
  int day;
  int hour;
  int minute;
  int second;
  uint16_t millisecond; // add this line to represent milliseconds (0~999)
};

DateTimeStruct currentDateTime; // Global date-time variable

// Struct for transmitting datetime over RF
struct DateTimePacket
{
  int year;
  int month;
  int day;
  int hour;
  int minute;
  int second;
  uint16_t millisecond;
};

// Acceleration
MPU6050 mpu(0x68);  // MPU6050 I2C address, default is 0x68
int16_t ax, ay, az; // Accelerometer readings
void read_print_acc()
{
  mpu.getAcceleration(&ax, &ay, &az);
  Serial.print("Accel X: ");
  Serial.print(ax);
  Serial.print(" Y: ");
  Serial.print(ay);
  Serial.print(" Z: ");
  Serial.println(az);
}

// Initialize NTP client
void initNTPTime()
{
  timeClient.begin();
  timeClient.update();
}

// Update NTP time periodically
void updateNTPTime()
{
  timeClient.update();
}

// Update DateTimeStruct from NTP time
void updateDateTimeStruct()
{
  timeClient.update();
  unsigned long epoch = timeClient.getEpochTime();

  // Convert epoch time to date and time
  currentDateTime.second = epoch % 60;
  currentDateTime.minute = (epoch / 60) % 60;
  currentDateTime.hour = (epoch / 3600) % 24;

  // Simple conversion to date (not handling leap years or DST)
  // This part uses Unix epoch days algorithm
  unsigned long days = epoch / 86400;
  int y = 1970;
  while (true)
  {
    bool leap = (y % 4 == 0 && y % 100 != 0) || (y % 400 == 0);
    int daysInYear = leap ? 366 : 365;
    if (days >= daysInYear)
    {
      days -= daysInYear;
      y++;
    }
    else
      break;
  }
  currentDateTime.year = y;

  static const int monthDays[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
  int m = 0;
  while (true)
  {
    int daysInMonth = monthDays[m];
    if (m == 1 && ((y % 4 == 0 && y % 100 != 0) || (y % 400 == 0)))
      daysInMonth++; // February leap year
    if (days >= daysInMonth)
    {
      days -= daysInMonth;
      m++;
    }
    else
      break;
  }
  currentDateTime.month = m + 1;
  currentDateTime.day = days + 1;
}

// LED
CRGB leds[NUM_LEDS]; // Array to hold LED color

// Touch Flag - volatile for ISR
volatile bool touch_triggered = false;

// Interrupt Service Routine (fast and minimal)
void onTouchInterrupt()
{
  touch_triggered = true;
}

// File IO
void FileIO()
{
  // Write to file
  File dataFile = SD.open("test.txt", FILE_WRITE);
  if (dataFile)
  {
    dataFile.println("Hello from Arduino UNO R4 WiFi!");
    dataFile.close();
    Serial.println("Data written to test.txt");
  }
  else
  {
    Serial.println("Failed to open file for writing.");
  }

  // Read from file
  dataFile = SD.open("test.txt");
  if (dataFile)
  {
    Serial.println("Reading from test.txt:");
    while (dataFile.available())
    {
      Serial.write(dataFile.read());
    }
    dataFile.close();
  }
  else
  {
    Serial.println("Failed to open file for reading.");
  }
}

// RF24 Radio
RF24 radio(9, 8); // CE on D9, CSN on D8
const byte address[6] = "NODE1";

/* INITIALIZATION */
void setup()
{
  // Serial Communication
  Serial.begin(9600);
  while (!Serial)
    ; // show nothing until Serial is ready

  // LED Initialization
  FastLED.addLeds<WS2812B, LED_PIN, GRB>(leds, NUM_LEDS);
  FastLED.setBrightness(50);
  leds[0] = CRGB::Red;    // Set first LED to red
  leds[1] = CRGB::Yellow; // Set second LED to yellow
  leds[2] = CRGB::Green;  // Set third LED to green
  leds[3] = CRGB::Blue;   // Set fourth LED to blue
  FastLED.show();
  Serial.println("LEDs initialized.");

  // Touch Sensor Initialization
  pinMode(TOUCH_SENSOR_PIN, INPUT); // Set touch sensor pin as input

  // Attach interrupt on rising edge (depends on your module)
  attachInterrupt(digitalPinToInterrupt(TOUCH_SENSOR_PIN), onTouchInterrupt, RISING);

  // WiFi Initialization
  Serial.println("Attempting to connect to WiFi...");
  while (WiFi.begin(ssid, pass) != WL_CONNECTED)
  {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("\nConnected to WiFi!");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());

  // NTP Initialization
  initNTPTime();
  updateDateTimeStruct();

  while (currentDateTime.year < 2000) // unsuccessful NTP usually lead to year 1970 while valid date usually has year > 2000
  {
    updateNTPTime(); // Update NTP time until valid date is received
    updateDateTimeStruct();
    delay(500); // Wait for a second before next update
  }

  // Print result
  Serial.print("Date: ");
  Serial.print(currentDateTime.year);
  Serial.print("-");
  Serial.print(currentDateTime.month);
  Serial.print("-");
  Serial.println(currentDateTime.day);

  Serial.print("Time: ");
  Serial.print(currentDateTime.hour);
  Serial.print(":");
  Serial.print(currentDateTime.minute);
  Serial.print(":");
  Serial.println(currentDateTime.second);

  // I2C Initialization
  Wire.begin();
  Serial.println("I2C initialized.");

  // MPU6050 Initialization
  mpu.initialize();
  Serial.println("MPU6050 initialized.");

  // SD Card Initialization
  if (!SD.begin(SD_CS_PIN))
  {
    Serial.println("SD card initialization failed!");
    while (1)
      ; // Halt
  }
  Serial.println("SD card initialized.");
  FileIO(); // Perform file IO operations
  Serial.println("File IO operations completed.");

  // RF24 Radio Initialization -  Transmitter
#ifdef RF_MODE_TRANSMITTER
  radio.begin();
  radio.setPALevel(RF24_PA_LOW);
  radio.setChannel(108);
  radio.openWritingPipe(address);
  radio.stopListening();
#endif // RF_MODE_TRANSMITTER

#ifdef RF_MODE_RECEIVER
  radio.begin();
  radio.setPALevel(RF24_PA_LOW);
  radio.setChannel(108);
  radio.openReadingPipe(0, address);
  radio.startListening();
#endif // RF_MODE_RECEIVER

  // clear the led array
  for (int i = 0; i < NUM_LEDS; i++)
  {
    leds[i] = CRGB::Black; // Clear all LEDs
  }
  FastLED.show(); // Update the LED strip
}

/* INFINITE LOOP */
void loop()
{

#ifdef RF_MODE_TRANSMITTER
  // update NTP time
  updateDateTimeStruct();

  // Prepare the message to send
  char msg[32];
  DateTimePacket packetToSend;
  packetToSend.year = currentDateTime.year;
  packetToSend.month = currentDateTime.month;
  packetToSend.day = currentDateTime.day;
  packetToSend.hour = currentDateTime.hour;
  packetToSend.minute = currentDateTime.minute;
  packetToSend.second = currentDateTime.second;
  packetToSend.millisecond = millis() % 1000;

  if (packetToSend.year > 2000)
  {
    bool success = radio.write(&packetToSend, sizeof(packetToSend));
    Serial.print("Sending datetime: ");
    snprintf(msg, sizeof(msg), "%04d-%02d-%02d %02d:%02d:%02d.%03d",
             packetToSend.year,
             packetToSend.month,
             packetToSend.day,
             packetToSend.hour,
             packetToSend.minute,
             packetToSend.second,
             packetToSend.millisecond);
    Serial.println(msg);

    Serial.println(success ? "[OK]" : "[Failed]");

    Serial.print("Sending: ");
    Serial.print(msg);
    Serial.println(success ? " [OK]" : " [Failed]");
  }
  else
  {
    Serial.println("Invalid date/time, not sending.");
  }

#endif // RF_MODE_TRANSMITTER

#ifdef RF_MODE_RECEIVER
  if (radio.available())
  {
    DateTimePacket receivedTime;
    radio.read(&receivedTime, sizeof(receivedTime));

    if (receivedTime.year < 2000)
    {
      Serial.println("Received invalid date/time, ignoring.");
      return;
    }
    else
    {
      // Update global date-time
      currentDateTime.year = receivedTime.year;
      currentDateTime.month = receivedTime.month;
      currentDateTime.day = receivedTime.day;
      currentDateTime.hour = receivedTime.hour;
      currentDateTime.minute = receivedTime.minute;
      currentDateTime.second = receivedTime.second;

      // Print full received time with milliseconds
      char buffer[40];
      snprintf(buffer, sizeof(buffer), "%04d-%02d-%02d %02d:%02d:%02d.%03d",
               receivedTime.year,
               receivedTime.month,
               receivedTime.day,
               receivedTime.hour,
               receivedTime.minute,
               receivedTime.second,
               receivedTime.millisecond);
      Serial.print("Received datetime: ");
      Serial.println(buffer);

      // === New: Estimate local offset based on millis() ===
      unsigned long local_ms = millis();
      unsigned long received_epoch_ms = receivedTime.second * 1000UL + receivedTime.millisecond;
      unsigned long local_epoch_ms = (local_ms % 60000);  // Assume local minute aligned
      long estimated_offset = (long)(received_epoch_ms - local_epoch_ms);  // in milliseconds

      Serial.print("Estimated time offset (ms): ");
      Serial.println(estimated_offset);
    }
  }
#endif // RF_MODE_RECEIVER


  // If touch flag is set, respond once
  if (touch_triggered)
  {
    touch_triggered = false; // Clear the flag

    Serial.println("Touch detected!");

    read_print_acc();

    // Turn LEDs on
    for (int i = 0; i < NUM_LEDS; i++)
    {
      leds[i] = CRGB::White;
    }
    FastLED.show();

    delay(300); // simple debounce

    // Turn LEDs off
    for (int i = 0; i < NUM_LEDS; i++)
    {
      leds[i] = CRGB::Black;
    }
    FastLED.show();
  }

  delay(1000);
}
