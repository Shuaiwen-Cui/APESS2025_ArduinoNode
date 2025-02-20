/*
 * 名称   : Servo_1
 * 功能   : 舵机旋转角度0 -> 90 -> 180，重复
 * 作者   : http://www.keyes-robot.com/ 
*/
#include <Servo.h>

Servo myservo;  //创建舵机对象来控制舵机

int servoPin = A1;  // 定义舵机引脚A1

void setup() {
  myservo.attach(servoPin);  //选择舵机引脚A1
}

void loop() {
  myservo.write(0); //旋转到0度
  delay(1000); //延迟1s
  myservo.write(90); //旋转到90度
  delay(1000); //延迟1s
  myservo.write(180); //旋转到180度
  delay(1000); //延迟1s
}