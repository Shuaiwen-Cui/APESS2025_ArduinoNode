/*  
 * 名称   : PAJ7620U2 gesture recognition
 * 功能   : 读取PAJ7620U2手势识别传感器传感器检测手势方向
 * 作者   : http://www.keyes-robot.com/ 
*/
#include <Wire.h>
#include "paj7620.h"
/* 
注意: 当你想识别前向/后向手势时，手势的反应时间必须小于GES_ENTRY_TIME(0.8s). 
        您也可以根据实际情况调整反应时间.
*/
#define GES_REACTION_TIME  500       // 您可以根据实际情况调整反应时间
#define GES_ENTRY_TIME    800       // 当你想识别前向/后向手势时，手势的反应时间必须小于GES_ENTRY_TIME(0.8s). 
#define GES_QUIT_TIME    1000

void setup(){
  uint8_t error = 0;
  Serial.begin(9600);
  Serial.println("\nPAJ7620U2 TEST DEMO: Recognize 9 gestures.");

  error = paj7620Init();      // 初始化Paj7620寄存器
  if (error) {
    Serial.print("INIT ERROR,CODE:");
    Serial.println(error);
  }
  else{
    Serial.println("INIT OK");
  }
  Serial.println("Please input your gestures:\n");
}

void loop(){
  uint8_t data = 0, data1 = 0, error;
  error = paj7620ReadReg(0x43, 1, &data);       // 读取 Reg_0x43/0x44 的手势结果.
  if (!error) {
    switch (data) {                  // 当检测到不同的手势时，变量`data`将被paj7620ReadReg设置为不同的值(0x43, 1, &data).
      case GES_RIGHT_FLAG:
        delay(GES_ENTRY_TIME);
        paj7620ReadReg(0x43, 1, &data);
        if(data == GES_FORWARD_FLAG) {
          Serial.println("Forward");
          delay(GES_QUIT_TIME);
        }
        else if(data == GES_BACKWARD_FLAG) {
          Serial.println("Backward");
          delay(GES_QUIT_TIME);
        }
        else{
          Serial.println("Right");
        }          
        break;
      case GES_LEFT_FLAG: 
        delay(GES_ENTRY_TIME);
        paj7620ReadReg(0x43, 1, &data);
        if(data == GES_FORWARD_FLAG) {
          Serial.println("Forward");
          delay(GES_QUIT_TIME);
        }
        else if(data == GES_BACKWARD_FLAG) {
          Serial.println("Backward");
          delay(GES_QUIT_TIME);
        }
        else{
          Serial.println("Left");
        }          
        break;
      case GES_UP_FLAG:
        delay(GES_ENTRY_TIME);
        paj7620ReadReg(0x43, 1, &data);
        if(data == GES_FORWARD_FLAG) {
          Serial.println("Forward");
          delay(GES_QUIT_TIME);
        }
        else if(data == GES_BACKWARD_FLAG) {
          Serial.println("Backward");
          delay(GES_QUIT_TIME);
        }
        else{
          Serial.println("Up");
        }          
        break;
      case GES_DOWN_FLAG:
        delay(GES_ENTRY_TIME);
        paj7620ReadReg(0x43, 1, &data);
        if(data == GES_FORWARD_FLAG) {
          Serial.println("Forward");
          delay(GES_QUIT_TIME);
        }
        else if(data == GES_BACKWARD_FLAG) {
          Serial.println("Backward");
          delay(GES_QUIT_TIME);
        }
        else{
          Serial.println("Down");
        }          
        break;
      case GES_FORWARD_FLAG:
        Serial.println("Forward");
        delay(GES_QUIT_TIME);
        break;
      case GES_BACKWARD_FLAG:     
        Serial.println("Backward");
        delay(GES_QUIT_TIME);
        break;
      case GES_CLOCKWISE_FLAG:
        Serial.println("Clockwise");
        break;
      case GES_COUNT_CLOCKWISE_FLAG:
        Serial.println("anti-clockwise");
        break;  
      default:
        paj7620ReadReg(0x44, 1, &data1);
        if (data1 == GES_WAVE_FLAG) 
        {
          Serial.println("wave");
        }
        break;
    }
  }
  delay(50);
}
