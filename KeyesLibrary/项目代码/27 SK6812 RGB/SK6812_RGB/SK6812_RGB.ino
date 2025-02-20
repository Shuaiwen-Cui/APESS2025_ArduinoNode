/*  
 * 名称   : sk6812 RGB
 * 功能   : 打开sk6812 RGB LED
 * 作者   : http://www.keyes-robot.com/ 
*/
#include <FastLED.h>

#define NUM_LEDS 4   //定义SK6812 RGB模块上LED灯珠数量
#define LED_PIN  3   //定义SK6812RGB模块控制引脚为D3
CRGB leds[NUM_LEDS];

void setup() {
  FastLED.addLeds<WS2812B, LED_PIN, GRB>(leds, NUM_LEDS);
  FastLED.setBrightness(50);   //设置SK6812 RGB的亮度
}

void loop() {
  effect3();
}

void effect3() {
  delay(50) ;{  
    // 为led[0]创建一个新的CHSV颜色
    leds[0] = CHSV(160, random8(), random8(100, 255));  
    // 把上一个颜色值复制过来, 从远端开始，将每个像素复制到下一个像素, 从而沿着带状“移动”图案.
    for (int i = NUM_LEDS - 1; i > 0; i--) {
      leds[i] = leds[i - 1];
    }
  }  
  FastLED.show();
}
