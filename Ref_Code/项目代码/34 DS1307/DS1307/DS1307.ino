/*  
 * 名称   : DS1307 Real Time Clock
 * 功能   : 读取DS1307时钟模块的年/月/日/时/分/秒/周
 * 作者   : http://www.keyes-robot.com/ 
*/
#include <Wire.h>
#include "RtcDS1307.h"  //DS1307时钟模块库
RtcDS1307<TwoWire> Rtc(Wire); //I2C接口:SDA引脚接A4, SCL引脚接A5

void setup(){
  Serial.begin(57600);//波特率设置为57600
  Wire.begin();        // 初始化I2C
  Rtc.Begin();
  Rtc.SetIsRunning(true);
  Rtc.SetDateTime(RtcDateTime(__DATE__, __TIME__));  
}

void loop(){
  // 打印年/月/日/小时/分/ 秒/周
  Serial.print(Rtc.GetDateTime().Year());
  Serial.print("/");
  Serial.print(Rtc.GetDateTime().Month());
  Serial.print("/");
  Serial.print(Rtc.GetDateTime().Day());
  Serial.print("    ");
  Serial.print(Rtc.GetDateTime().Hour());
  Serial.print(":");
  Serial.print(Rtc.GetDateTime().Minute());
  Serial.print(":");
  Serial.print(Rtc.GetDateTime().Second());
  Serial.print("    ");
  Serial.println(Rtc.GetDateTime().DayOfWeek());
  delay(1000);//延迟1秒
}