#include <Arduino.h>

/*
 * Name   : DS1307 Real Time Clock
 * Function: Reads the year/month/day/hour/minute/second/dayOfWeek from the DS1307 clock module
 * Author : http://www.keyes-robot.com/
*/

#include <Wire.h>
#include "RtcDS1307.h"  // DS1307 clock module library
RtcDS1307<TwoWire> Rtc(Wire); // I2C interface: SDA -> A4, SCL -> A5

void setup(){
  Serial.begin(9600); // Set baud rate to 9600
  Wire.begin();        // Initialize I2C
  Rtc.Begin();
  Rtc.SetIsRunning(true);
  // This will reset the clock to the compilation date/time every time the board resets
  Rtc.SetDateTime(RtcDateTime(__DATE__, __TIME__));
}

void loop(){
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