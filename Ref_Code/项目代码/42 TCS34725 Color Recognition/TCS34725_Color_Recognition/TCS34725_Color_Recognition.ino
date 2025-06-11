/*  
 * 名称   : TCS34725 Color Recognition
 * 功能   : 读取TCS34725颜色传感器检测的颜色值
 * 作者   : http://www.keyes-robot.com/ 
*/
#include "Adafruit_TCS34725.h"
/* Adafruit TCS34725 breakout库的示例代码 */

/* Connect SCL    to analog 5 (A5)
   Connect SDA    to analog 4 (A4)
   Connect  V     to DC 5V(V)
   Connect GROUND to common ground */
   
/* 使用默认值初始化 (int time = 2.4ms, gain = 1x) */
// Adafruit_TCS34725 tcs = Adafruit_TCS34725();

/* 用特定的int时间和增益值初始化 */
Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_700MS, TCS34725_GAIN_1X);

void setup(void) {
  Serial.begin(9600); 
  if (tcs.begin()) {
    Serial.println("Found sensor");
  } else {
    Serial.println("No TCS34725 found ... check your connections");
    while (1);
  } 
  // 现在准备阅读了!
}

void loop(void) {
  uint16_t r, g, b, c, colorTemp, lux; 
  tcs.getRawData(&r, &g, &b, &c);
  colorTemp = tcs.calculateColorTemperature(r, g, b);
  lux = tcs.calculateLux(r, g, b);
  
  Serial.print("Color Temp: "); Serial.print(colorTemp, DEC); Serial.print(" K - ");
  Serial.print("Lux: "); Serial.print(lux, DEC); Serial.print(" - ");
  Serial.print("R: "); Serial.print(r, DEC); Serial.print(" ");
  Serial.print("G: "); Serial.print(g, DEC); Serial.print(" ");
  Serial.print("B: "); Serial.print(b, DEC); Serial.print(" ");
  Serial.print("C: "); Serial.print(c, DEC); Serial.print(" ");
  Serial.println(" ");
}
