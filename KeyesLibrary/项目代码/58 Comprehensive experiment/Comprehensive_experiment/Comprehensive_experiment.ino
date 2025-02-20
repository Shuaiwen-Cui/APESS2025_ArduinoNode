/*
 * 名称   : Comprehensive experiment
 * 功能   : 多个传感器/模块协同工作
 * 作者   : http://www.keyes-robot.com/ 
*/
#include <FastLED.h>
#include "xht11.h"

#define NUM_LEDS 4   //定义SK6812 RGB模块上LED灯珠数量
#define LED_PIN  3   //定义SK6812 RGB模块控制引脚为D3
CRGB leds[NUM_LEDS];

//摇杆模块接口
int xyzPins[] = {A3, A2, 7};   //x, y, z

//滑动电位器模块引脚连接到端口A4
int resPin = A4;

//避障传感器引脚连接到IO端口D5
int Avoid = 5;

//超声波传感器的接口
int Trig = A0;
int Echo = A1;

//电容触摸传感器的端口为D8
int Touch = 8;

int PushCounter = 0;//存储键被按下的次数
int yushu = 0;

xht11 xht(12); //定义XHT11的引脚为D12
unsigned char dht[4] = {0, 0, 0, 0};//只接收数据的前32位，不接收奇偶校验位

bool ir_flag = 1;
float out_X, out_Y, out_Z;

void counter() {
  delay(10);
  ir_flag = 0;
  if (!digitalRead(Touch)) {
    PushCounter++;
  }
}

void setup() {
  Serial.begin(9600);//波特率设置为9600
  pinMode(xyzPins[0], INPUT); //x axis. 
  pinMode(xyzPins[1], INPUT); //y axis. 
  pinMode(xyzPins[2], INPUT_PULLUP);   //Z轴是一个按钮
  pinMode(Touch, INPUT);//电容触摸传感器
  attachInterrupt(digitalPinToInterrupt(Touch), counter, FALLING);  //外部中断0，下降沿触发
  pinMode(Avoid, INPUT);//避障传感器
  pinMode(resPin, INPUT);//滑动电位器
  pinMode(Trig, OUTPUT);//超声波传感器
  pinMode(Echo, INPUT);
  FastLED.addLeds<WS2812B, LED_PIN, GRB>(leds, NUM_LEDS);
  FastLED.setBrightness(50);   //设置SK6812 RGB的亮度
  delay(1000);
}

void loop() {
  yushu = PushCounter % 6;
  if (yushu == 0) {  //余数为0
    yushu_0();  //rgb显示
} else if (yushu == 1) {  //余数是1
    yushu_1();  //避障传感器检测障碍物
} else if (yushu == 2) {  //余数是2
    yushu_2();  //显示摇杆值
} else if (yushu == 3) {  //余数是3
   yushu_3();  //显示滑动电位器的模拟值
} else if (yushu == 4) {  //余数是4
   yushu_4();  //显示XHT11温湿度传感器的温湿度值
} else if (yushu == 5) {  //余数是5
   yushu_5();  //显示超声波检测到的距离
  } 
}

//SK6812 RGB模块上的4个LED灯珠亮不同颜色的灯
void yushu_0() {
  fill_solid(leds, NUM_LEDS, CRGB::Red);  //亮红色灯
  FastLED.show();
  delay(100);
  fill_solid(leds, NUM_LEDS, CRGB::Green);  //亮绿色灯
  FastLED.show();
  delay(100);
  fill_solid(leds, NUM_LEDS, CRGB::Blue);  //亮蓝色灯
  FastLED.show();
  delay(100);
  fill_solid(leds, NUM_LEDS, CRGB::Orange);  //亮橙色灯
  FastLED.show();
  delay(100);
  fill_solid(leds, NUM_LEDS, CRGB::Yellow);  //亮黄色灯
  FastLED.show();
  delay(100);
  fill_solid(leds, NUM_LEDS, CRGB::Purple);  //亮紫色灯
  FastLED.show();
  delay(100);
  fill_solid(leds, NUM_LEDS, CRGB::Gold);  //亮金色灯
  FastLED.show();
  delay(100);
  fill_solid(leds, NUM_LEDS, CRGB::Pink);  //亮粉红色灯
  FastLED.show();
  delay(100);
  fill_solid(leds, NUM_LEDS, CRGB::Magenta);  //亮品红色灯
  FastLED.show();
  delay(100);
  fill_solid(leds, NUM_LEDS, CRGB::White);   // 亮白色灯
  FastLED.show();
  delay(100);
}

//读避障传感器的数字信号
void yushu_1() {
  int val = digitalRead(Avoid);//读取避障传感器的数字电平输出
  Serial.print(val);//串口打印值
  if (val == 0) {//障碍物检测
    Serial.println("   There are obstacles");
  }
  else {//未发现障碍物
    Serial.println("   All going well");
  }
  delay(100);
}

//读摇杆模块的值
void yushu_2() {
  int xVal = analogRead(xyzPins[0]);
  int yVal = analogRead(xyzPins[1]);
  int zVal = digitalRead(xyzPins[2]);
  Serial.println("X,Y,Z: " + String(xVal) + ", " +  String(yVal) + ", " + String(zVal));
  delay(500);
}

//读滑动电位器的模拟值
void yushu_3() {
  int adcVal = analogRead(resPin); 
  Serial.println(adcVal);
  delay(100);
}

//读XHT11温湿度传感器的温湿度
void yushu_4() {
  if (xht.receive(dht)) {  //检查正确时返回true
    Serial.print("RH:");
    Serial.print(dht[0]);  //湿度的积分部分，DHT[1]是分数部分
    Serial.print("%  ");
    Serial.print("Temp:");
    Serial.print(dht[2]);  //温度的积分部分，DHT[3]是分数部分
    Serial.println("C");
  } else {   //读取错误
    Serial.println("sensor error");
  }
  delay(200);
}

//超声波传感器测距
void yushu_5() {
  float distance = checkdistance();
  Serial.print("distance:");
  Serial.print(distance);
  Serial.println("cm");
  delay(100);
}

float checkdistance() {
  digitalWrite(Trig, LOW);
  delayMicroseconds(2);
  digitalWrite(Trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(Trig, LOW);
  float distance = pulseIn(Echo, HIGH) / 58.00;
  delay(10);
  return distance;
}
