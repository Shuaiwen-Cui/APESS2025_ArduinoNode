/**
   名字：adxl345_io.h
   功能：实现自定义库头文件
   适用于arduino, esp32, raspberry pi pico
   作者：邓飞
   时间：2021/2/25
*/

#ifndef _adxl345_io_H__
#define _adxl345_io_H__

#include "Arduino.h"
#define  DATA_FORMAT   0x31
#define  BW_RATE       0x2C
#define  POWER_CTL     0x2D
#define  INT_ENABLE    0x2E
#define  OFSX          0x1E
#define  OFSY          0x1F
#define  OFSZ          0x20
#define  slvAddr       0x53

class adxl345
{
  private:
    int SDA;
    int SCL;
    
  public:
    adxl345(int _sda, int _scl);
    void readXYZ(float *out_X, float *out_Y, float *out_Z);
    void Init();
    void ADXL345_writeByte(unsigned char addr, unsigned char data);
    void ADXL345_readByte(unsigned char addr, unsigned char *dat, unsigned char len);
    void IIC_Start();
    void IIC_Stop();
    void IIC_SendACK(bool ack);
    bool IIC_RecvACK();
    void IIC_SendByte(unsigned char dat);
    unsigned char IIC_RecvByte();
};

#endif