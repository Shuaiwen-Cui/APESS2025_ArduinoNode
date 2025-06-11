#include <Arduino.h>
#include <Wire.h>
#include <MPU6050.h>

MPU6050 mpu(0x69);  // AD0 = HIGH, so address is 0x69

void setup() {
  Serial.begin(9600);
  Wire.begin();

  mpu.initialize();

  if (mpu.testConnection()) {
    Serial.println("MPU6050 connected successfully");
  } else {
    Serial.println("MPU6050 connection failed");
    while (1);
  }
}

void loop() {
  int16_t ax, ay, az;
  mpu.getAcceleration(&ax, &ay, &az);

  Serial.print("Accel X: "); Serial.print(ax);
  Serial.print(" Y: "); Serial.print(ay);
  Serial.print(" Z: "); Serial.println(az);

  delay(500);
}
