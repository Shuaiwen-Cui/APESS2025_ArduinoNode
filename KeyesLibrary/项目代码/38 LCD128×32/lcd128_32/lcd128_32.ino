/*  
 * 名称   : lcd128*32
 * 功能   : LCD128*32 显示字符串
 * 作者   : http://www.keyes-robot.com/ 
*/
#include <lcd.h>

lcd Lcd;  //LCD128*32屏的I2C接口:SDA引脚接A4, SCL引脚接A5

void setup() {
  Lcd.Init();  //lcd初始化
  Lcd.Clear();  //lcd清屏
}

void loop() {
  Lcd.Cursor(0, 7); //设置显示的位置
  Lcd.Display("KEYES"); //设置视图显示
  Lcd.Cursor(1, 0);
  Lcd.Display("ABCDEFGHIJKLMNOPQR");
  Lcd.Cursor(2, 0);
  Lcd.Display("123456789+-*/<>=$@");
  Lcd.Cursor(3, 0);
  Lcd.Display("%^&(){}:;'|?,.~\\[]");
}