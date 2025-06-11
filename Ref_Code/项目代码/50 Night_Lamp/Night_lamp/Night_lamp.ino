/*  
 * 名称   : Night_lamp
 * 功能   : 光敏传感器控制SK6812 RGB模块上4个LED灯珠亮灭
 * 作者   : http://www.keyes-robot.com/ 
*/
#include <FastLED.h>

int Photosensor = A0;  //定义光敏传感器的控制引脚为A0

#define NUM_LEDS 4   //定义SK6812 RGB模块上LED灯珠数量
#define LED_PIN  3   //定义SK6812 RGB模块控制引脚为D3
CRGB leds[NUM_LEDS];

void setup() {
  Serial.begin(9600); //波特率设置为9600
  pinMode(Photosensor, INPUT);  //设置光敏传感器的引脚为输入模式
  FastLED.addLeds<WS2812B, LED_PIN, GRB>(leds, NUM_LEDS);
  FastLED.setBrightness(50); //设置SK6812 RGB模块上4个LED灯珠的亮度
}

void loop() {
  int val = analogRead(Photosensor); //读取模拟值
  Serial.println(val); // 串口打印
  if(val < 200){ //低于阈值
    fill_solid(leds, NUM_LEDS, CRGB::White);   // SK6812 RGB模块4个LED灯珠亮白灯
    FastLED.show();
  }else{ //否则
    fill_solid(leds, NUM_LEDS, CRGB::Black);  // SK6812 RGB模块4个LED灯珠不亮
    FastLED.show();
  }
  delay(100);
}