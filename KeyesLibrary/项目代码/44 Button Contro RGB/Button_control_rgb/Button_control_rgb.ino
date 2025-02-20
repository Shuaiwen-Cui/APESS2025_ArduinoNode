/* 
 * 名称   : Button_control_rgb
 * 功能   : 模拟一个小台灯
 * 作者   : http://www.keyes-robot.com/ 
*/
#include <FastLED.h>

#define NUM_LEDS 4   //定义SK6812 RGB模块上LED灯珠数量
#define LED_PIN  3   //定义SK6812 RGB模块控制引脚为D3
CRGB leds[NUM_LEDS];

#define PIN_BUTTON  5  //将自锁按键的引脚连接到D5
int val = 0;            //用于存储键值

void setup() {
  Serial.begin(9600);//启动串口监视器，设置波特率为9600
  FastLED.addLeds<WS2812B, LED_PIN, GRB>(leds, NUM_LEDS);
  FastLED.setBrightness(50);   //设置SK6812 RGB的亮度
  pinMode(PIN_BUTTON, INPUT);  //设置自锁按键的引脚为输入模式
}

// 循环函数会一直运行下去
void loop() {
  val = digitalRead(PIN_BUTTON);  //读取自锁按键的值并将其赋值给变量val
  Serial.println(val);          //打印变量val的值
  if (val == 0) {             //按下自锁按键时读取到低电平，并打印出相关的信息
    fill_solid(leds, NUM_LEDS, CRGB::White);   // SK6812 RGB模块4个LED灯珠亮白灯
    FastLED.show();
  }
  else { 
    fill_solid(leds, NUM_LEDS, CRGB::Black);  // SK6812 RGB模块4个LED灯珠不亮
    FastLED.show(); 
  } 
}
