/*  
 * 名称   : bmp388 barometric pressure
 * 功能   : 读取bmp388气压传感器检测的值
 * 作者   : http://www.keyes-robot.com/ 
*/
#include "Waveshare_BMP388.h"

void setup() {  //把你的设置代码放在这里，只运行一次:
  bool bRet;
  PRESS_EN_SENSOR_TYPY enPressureType;
  Serial.begin(115200);
  pressSensorInit( &enPressureType );
  if(PRESS_EN_SENSOR_TYPY_BMP388 == enPressureType){
    Serial.println("Pressure sersor is BMP388");
  }
  else{
    Serial.println("Pressure sersor NULL");
  }
  Serial.println("/-------------------------------------------------------------/");
  delay(1000);
}

void loop() {  // 把主代码放在这里，反复运行:
  int32_t s32PressureVal = 0, s32TemperatureVal = 0, s32AltitudeVal = 0;
  pressSensorDataGet(&s32TemperatureVal, &s32PressureVal, &s32AltitudeVal);
  Serial.print("Pressure : "); 
  Serial.print((float)s32PressureVal / 100);
  Serial.print(" Pa"); 
  Serial.print("   Altitude : "); 
  Serial.print((float)s32AltitudeVal / 100);
  Serial.print(" m");
  Serial.print("   Temperature : "); 
  Serial.print((float)s32TemperatureVal / 100);
  Serial.print(" ℃");
  Serial.println();
  delay(50);  
}
