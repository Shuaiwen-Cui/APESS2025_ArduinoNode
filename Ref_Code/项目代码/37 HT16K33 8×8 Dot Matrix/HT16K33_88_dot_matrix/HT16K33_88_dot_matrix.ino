 /*
 * 名称   : 8×8 Dot-matrix Display
 * 功能   : 8x8 LED点阵显示“笑脸”图案
 * 作者   : http://www.keyes-robot.com/ 
*/
#include <Matrix.h>  //HT16K33 8*8点阵模块库

Matrix myMatrix(A4,A5);  //I2C接口:SDA引脚接A4, SCL引脚接A5
uint8_t LedArray1[8]={0x00,0x42,0x41,0x09,0x09,0x41,0x42,0x00};
uint8_t  LEDArray[8];

void setup(){
  myMatrix.begin(0x70);  //初始化矩阵
}

void loop(){
  myMatrix.clear();
  for(int i=0; i<8; i++)
  {
    LEDArray[i]=LedArray1[i];
    for(int j=7; j>=0; j--)
    {
      if((LEDArray[i]&0x01)>0)
      myMatrix.drawPixel(j, i,1);
      LEDArray[i] = LEDArray[i]>>1;
    }
  }
  myMatrix.writeDisplay();
}