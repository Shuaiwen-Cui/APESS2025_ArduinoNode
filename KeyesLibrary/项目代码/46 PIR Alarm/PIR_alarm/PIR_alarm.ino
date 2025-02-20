/*  
 * 名称   : PIR alarm
 * 功能   : PIR控制蜂鸣器和SK6812 RGB模块
 * 作者   : http://www.keyes-robot.com/ 
*/
#include <FastLED.h>

#define NUM_LEDS 4     //定义SK6812 RGB模块上LED灯珠数量
#define LED_PIN  3     //定义SK6812 RGB模块控制引脚为D3
CRGB leds[NUM_LEDS]; 

#define PIR_PIN  5     //PIR运动传感器控制引脚为D5
#define BUZZER_PIN  8  //定义有源蜂鸣器控制引脚为D8

int item = 0;

void setup() {
  Serial.begin(9600);//启动串口监视器，设置波特率为9600
  pinMode(PIR_PIN, INPUT);  //设置PIR运动传感器的引脚为输入模式
  pinMode(BUZZER_PIN, OUTPUT); //设置有源蜂鸣器的引脚为输出模式
  FastLED.addLeds<WS2812B, LED_PIN, GRB>(leds, NUM_LEDS);
  FastLED.setBrightness(50);   //设置SK6812 RGB的亮度
}

void loop() {
  item = digitalRead(PIR_PIN);//读取红外热释传感器输出的数字信号
  Serial.println(item);          //打印变量item的值
  if (item == 1) {  //运动检测
    digitalWrite(BUZZER_PIN, HIGH); //打开蜂鸣器
    fill_solid(leds, NUM_LEDS, CRGB::Red);   // SK6812RGB模块4个LED灯珠亮红灯
    FastLED.show();
    delay(200);//延迟 200ms
    digitalWrite(BUZZER_PIN, LOW); //关掉蜂鸣器
    fill_solid(leds, NUM_LEDS, CRGB::Black);  // SK6812 RGB模块4个LED灯珠不亮
    FastLED.show();
    delay(200);//延迟 200ms
  } else {  //没有检测到任何信号或数据
    digitalWrite(BUZZER_PIN, LOW); //关掉蜂鸣器
    fill_solid(leds, NUM_LEDS, CRGB::Black);  // SK6812 RGB模块4个LED灯珠不亮
    FastLED.show();
  }
}