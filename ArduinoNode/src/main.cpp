#include <Arduino.h>

/* [1] Main Control Test */

// void setup()
// {
//   Serial.begin(9600);
// }

// void loop()
// {
//   Serial.println("Hello, World!");
//   delay(1000);
// }

/* [2] RTC DS1307 */
// /*
//  * Name   : DS1307 Real Time Clock
//  * Function: Reads the year/month/day/hour/minute/second/dayOfWeek from the DS1307 clock module
//  * Author : http://www.keyes-robot.com/
// */

// #include <Wire.h>
// #include "RtcDS1307.h"  // DS1307 clock module library
// RtcDS1307<TwoWire> Rtc(Wire); // I2C interface: SDA -> A4, SCL -> A5

// void setup(){
//   Serial.begin(57600); // Set baud rate to 57600
//   Wire.begin();        // Initialize I2C
//   Rtc.Begin();
//   Rtc.SetIsRunning(true);
//   // This will reset the clock to the compilation date/time every time the board resets
//   Rtc.SetDateTime(RtcDateTime(__DATE__, __TIME__));
// }

// void loop(){
//   // Print year/month/day/hour/minute/second/dayOfWeek
//   Serial.print(Rtc.GetDateTime().Year());
//   Serial.print("/");
//   Serial.print(Rtc.GetDateTime().Month());
//   Serial.print("/");
//   Serial.print(Rtc.GetDateTime().Day());
//   Serial.print("    ");
//   Serial.print(Rtc.GetDateTime().Hour());
//   Serial.print(":");
//   Serial.print(Rtc.GetDateTime().Minute());
//   Serial.print(":");
//   Serial.print(Rtc.GetDateTime().Second());
//   Serial.print("    ");
//   Serial.println(Rtc.GetDateTime().DayOfWeek());
//   delay(1000); // Delay 1 second
// }

/* [3] RTC ADXL345 */
// /*
//  * Name   : ADXL345
//  * Function : Reads the X/Y/Z values from the ADXL345
//  * Author : http://www.keyes-robot.com/
//  */

//  #include "adxl345_io.h"
//  adxl345 adxl345(A0, A1); // I2C interface: SDA -> A0, SCL -> A1

//  float out_X, out_Y, out_Z;

//  void setup() {
//    Serial.begin(57600); // Start the serial monitor at 57600 baud
//    adxl345.Init();
//  }

//  void loop() {
//    adxl345.readXYZ(&out_X, &out_Y, &out_Z);
//    Serial.print(out_X);
//    Serial.print("g   ");
//    Serial.print(out_Y);
//    Serial.print("g   ");
//    Serial.print(out_Z);
//    Serial.println("g");
//    delay(100);
//  }

/* [x] Combined: RTC ADXL345 */
#include <Wire.h>
#include "RtcDS1307.h" // DS1307 clock module library
#include "adxl345_io.h"

RtcDS1307<TwoWire> Rtc(Wire); // I2C interface: SDA -> A4, SCL -> A5
adxl345 adxl345(A0, A1);      // I2C interface: SDA -> A0, SCL -> A1
float out_X, out_Y, out_Z;

void setup()
{
  Serial.begin(57600); // Set baud rate to 57600
  Wire.begin();        // Initialize I2C
  Rtc.Begin();
  Rtc.SetIsRunning(true);
  // This will reset the clock to the compilation date/time every time the board resets
  Rtc.SetDateTime(RtcDateTime(__DATE__, __TIME__));
  adxl345.Init();
}

void loop()
{

  adxl345.readXYZ(&out_X, &out_Y, &out_Z);
  Serial.print(out_X);
  Serial.print("g   ");
  Serial.print(out_Y);
  Serial.print("g   ");
  Serial.print(out_Z);
  Serial.print("g   ");

  // Print year/month/day/hour/minute/second/dayOfWeek
  Serial.print(Rtc.GetDateTime().Year());
  Serial.print("/");
  Serial.print(Rtc.GetDateTime().Month());
  Serial.print("/");
  Serial.print(Rtc.GetDateTime().Day());
  Serial.print("    ");
  Serial.print(Rtc.GetDateTime().Hour());
  Serial.print(":");
  Serial.print(Rtc.GetDateTime().Minute());
  Serial.print(":");
  Serial.print(Rtc.GetDateTime().Second());
  Serial.print("    ");
  Serial.println(Rtc.GetDateTime().DayOfWeek());

  delay(1000); // Delay 1 second
}
