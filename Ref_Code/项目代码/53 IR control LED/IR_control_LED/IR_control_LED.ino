/*  
 * 名称   : IR Control LED
 * 功能   : 红外遥控SK6812RGB模块上4个LED灯珠亮不同颜色灯
 * 作者   : http://www.keyes-robot.com/ 
*/
#include <Arduino.h>
#include <IRremote.hpp>
#include <FastLED.h>

#define IR_RECEIVE_PIN  5   // 定义红外接收模块引脚D5
IRrecv irrecv(IR_RECEIVE_PIN);     // 创建一个用于接收类的类对象
decode_results results;     // 创建一个解码结果类对象

#define NUM_LEDS 4   //定义SK6812 RGB模块上LED灯珠数量
#define LED_PIN  3   //定义SK6812 RGB模块控制引脚为D3
CRGB leds[NUM_LEDS];

boolean flag = true;  //LED标志钻头

void setup() {
  Serial.begin(9600);
  IrReceiver.begin(IR_RECEIVE_PIN, ENABLE_LED_FEEDBACK);  // 启动接收器
  FastLED.addLeds<WS2812B, LED_PIN, GRB>(leds, NUM_LEDS);
  FastLED.setBrightness(50);   //设置SK6812 RGB的亮度
}

void loop() {
  if (IrReceiver.decode()) {
      Serial.print(IrReceiver.decodedIRData.decodedRawData, HEX);  // 打印原始数据
      // IrReceiver.printIRResultShort(&Serial); // 在一行中打印接收到的完整数据
      // IrReceiver.printIRSendUsage(&Serial);  // 打印发送这些数据所需的语句
      handleControl(IrReceiver.decodedIRData.decodedRawData);      // 处理来自远程控制的命令
      IrReceiver.resume(); // 启用接收下一个值
  }
}

void handleControl(unsigned long value){
  if (value == 0xBF40FF00 && flag == true){ // 接收数字“OK” 
    fill_solid(leds, NUM_LEDS, CRGB::White);   // SK6812 RGB模块4个LED灯珠亮白灯
    FastLED.show();
    delay(10);
    Serial.println("  led on");
    flag = false;
  } 
  else if (value == 0xBF40FF00 && flag == false){ // 接收数字“OK”
    fill_solid(leds, NUM_LEDS, CRGB::Black);  // SK6812 RGB模块4个LED灯珠不亮
    FastLED.show(); 
    delay(10);
    Serial.println("  led off"); 
    flag = true;
  }
  else if(value == 0xE916FF00){
    fill_solid(leds, NUM_LEDS, CRGB::Red);  // SK6812 RGB模块4个LED灯珠亮红色灯
    FastLED.show();
    delay(10);
    Serial.println("  red led");

  } 
  else if(value == 0xE619FF00){
    fill_solid(leds, NUM_LEDS, CRGB::Green);  // SK6812 RGB模块4个LED灯珠亮绿色灯
    FastLED.show();
    delay(10);
    Serial.println("  green led");
  } 
  else if(value == 0xF20DFF00){
    fill_solid(leds, NUM_LEDS, CRGB::Blue);  // SK6812 RGB模块4个LED灯珠亮蓝色灯
    FastLED.show();
    delay(10);
    Serial.println("  blue led");
  }
  else if(value == 0xF30CFF00){
    fill_solid(leds, NUM_LEDS, CRGB::Orange);  // SK6812 RGB模块4个LED灯珠亮橙色灯
    FastLED.show();
    delay(10);
    Serial.println("  orange led");
  }
  else if(value == 0xE718FF00){
    fill_solid(leds, NUM_LEDS, CRGB::Yellow);  // SK6812 RGB模块4个LED灯珠亮黄色灯
    FastLED.show();
    delay(10);
    Serial.println("  yellow led");
  }
  else if(value == 0xA15EFF00){
    fill_solid(leds, NUM_LEDS, CRGB::Purple);  // SK6812 RGB模块4个LED灯珠亮紫色灯
    FastLED.show();
    delay(10);
    Serial.println("  purple led");
  }
  else if(value == 0xF708FF00){
    fill_solid(leds, NUM_LEDS, CRGB::Gold);  // SK6812 RGB模块4个LED灯珠亮金色灯
    FastLED.show();
    delay(10);
    Serial.println("  gold led");
  }
  else if(value == 0xE31CFF00){
    fill_solid(leds, NUM_LEDS, CRGB::Pink);  // SK6812 RGB模块4个LED灯珠亮粉红色灯
    FastLED.show();
    delay(10);
    Serial.println("  pink led");
  }
  else if(value == 0xA55AFF00){
    fill_solid(leds, NUM_LEDS, CRGB::Magenta);  // SK6812 RGB模块4个LED灯珠亮品红色灯
    FastLED.show();
    delay(10);
    Serial.println("  magenta led");
  }
}