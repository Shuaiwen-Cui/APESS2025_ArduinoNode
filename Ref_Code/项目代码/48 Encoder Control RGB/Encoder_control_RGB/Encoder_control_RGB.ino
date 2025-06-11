/*  
 * 名称   : Encoder control RGB
 * 功能   : 旋转编码器控制RGB来呈现不同的效果
 * 作者   : http://www.keyes-robot.com/ 
*/
#include <FastLED.h>

//旋转编码器的接口
int Encoder_CLK  = 2;
int Encoder_DT  = 3;
int Encoder_Switch = 4;

int Previous_Output;
int Encoder_Count;

#define NUM_LEDS 4     //定义SK6812 RGB模块上LED灯珠数量
#define LED_PIN  5     //定义SK6812 RGB模块控制引脚为D5
CRGB leds[NUM_LEDS];

int val;

void setup() {
  Serial.begin(9600);

  //引脚模式声明
  pinMode (Encoder_DT, INPUT);
  pinMode (Encoder_CLK, INPUT);
  pinMode (Encoder_Switch, INPUT);

  Previous_Output = digitalRead(Encoder_DT); //读取输出DT的初始值
  FastLED.addLeds<WS2812B, LED_PIN, GRB>(leds, NUM_LEDS);
  FastLED.setBrightness(50);   //设置SK6812 RGB的亮度
}

void loop() {
  if (digitalRead(Encoder_DT) != Previous_Output)
  {
    if (digitalRead(Encoder_CLK) != Previous_Output)
    {
      Encoder_Count ++;
      Serial.print(Encoder_Count);
      Serial.print("  ");
      val = Encoder_Count % 3;
      Serial.println(val);
    }
    else
    {
      Encoder_Count--;
      Serial.print(Encoder_Count);
      Serial.print("  ");
      val = Encoder_Count % 3;
      Serial.println(val);
    }
  }

  Previous_Output = digitalRead(Encoder_DT);

  if (digitalRead(Encoder_Switch) == 0)
  {
    delay(5);
    if (digitalRead(Encoder_Switch) == 0) {
      Serial.println("Switch pressed");
      while (digitalRead(Encoder_Switch) == 0);
    }
  }
  if (val == 0) {
    //红色灯
    fill_solid(leds, NUM_LEDS, CRGB::Red);   // SK6812RGB模块4个LED灯珠亮红色灯
    FastLED.show();
  } else if (val == 1) {
    //绿色灯
    fill_solid(leds, NUM_LEDS, CRGB::Green);   // SK6812RGB模块4个LED灯珠亮绿色灯
    FastLED.show();
  } else {
    //蓝色灯
    fill_solid(leds, NUM_LEDS, CRGB::Blue);   // SK6812RGB模块4个LED灯珠亮蓝色灯
    FastLED.show();
  }
}