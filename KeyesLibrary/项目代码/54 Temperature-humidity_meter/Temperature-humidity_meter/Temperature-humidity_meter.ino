/*  
 * 名称   : Temperature-humidity meter
 * 功能   : LCD128*32屏显示温度和湿度
 * 作者   : http://www.keyes-robot.com/ 
*/
#include "xht11.h"
#include <lcd.h>

xht11 xht(3); //定义XHT11的引脚为D3
unsigned char dht[4] = {0, 0, 0, 0};// 只接收数据的前32位，不接收奇偶校验位

lcd Lcd;  //LCD128*32屏的I2C接口:SDA引脚接A4, SCL引脚接A5

void setup(){
  Lcd.Init();  //lcd初始化
  Lcd.Clear();  //lcd清屏
}
char string[10];

//LCD128*32屏显示温度值和湿度值
void loop(){
  if (xht.receive(dht)) { //正确检查时返回true
    }
  Lcd.Cursor(0,0); //设置显示的位置
  Lcd.Display("Temper:"); //显示字符串Temper:
  Lcd.Cursor(0,8);
  Lcd.Display_Num(dht[2]); //显示温度值
  Lcd.Cursor(0,11);
  Lcd.Display("C");
  Lcd.Cursor(2,0); 
  Lcd.Display("humid:");
  Lcd.Cursor(2,8);
  Lcd.Display_Num(dht[0]);
  Lcd.Cursor(2,11);
  Lcd.Display("%");
  delay(200);
}
