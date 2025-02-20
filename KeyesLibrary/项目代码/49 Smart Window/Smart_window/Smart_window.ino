/*  
 * 名称   : smart window
 * 功能   : 水滴传感器控制舵机转动
 * 作者   : http://www.keyes-robot.com/ 
*/
#include <Servo.h>   //导入舵机库文件

#define PIN_ADC  A2   //定义水滴传感器的引脚A2

int adcVal = 0;       //保存液滴传感器输出的ADC值的变量
int servoPin = A1;    // 定义舵机引脚A1
Servo myservo;        //定义舵机类的实例image.png

void setup(){
  Serial.begin(9600);
  pinMode(PIN_ADC, INPUT);  //设置水滴传感器的引脚为输入模式
  myservo.attach(servoPin);  //选择舵机引脚A1
  myservo.write(180); //打开窗户
  delay(500); //延迟500毫秒
}

void loop(){
  adcVal = analogRead(PIN_ADC); //水滴传感器连接到模拟端口A2
  Serial.println(adcVal);
  if (adcVal > 400) { //模拟值大于400
    myservo.write(0);  //关上窗户
    delay(500); //给舵机转向的时间
  } else { // 没有下雨
    myservo.write(180); //打开窗户
    delay(500); //延迟500毫秒
  }
}