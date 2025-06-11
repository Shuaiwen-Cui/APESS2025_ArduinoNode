/**
 * 名字：adxl345_io.cpp
 * 功能：adxl345控制源文件
 * 适用于arduino, esp32, raspberry pi pico
 * 作者：邓飞
 * 时间：2022.2.25
 */

#include "adxl345_io.h"
#include "Arduino.h"

adxl345::adxl345(int _sda, int _scl)
{
  SDA = _sda;
  SCL = _scl;
  pinMode(SDA, OUTPUT); //SDA总线为输出模式
  pinMode(SCL, OUTPUT); //SCL总线为输出模式
}

/* ADXL345读加速度值函数out_X，out_Y，out_Z为数据指针
 */
void adxl345::readXYZ(float *out_X, float *out_Y, float *out_Z) {
  unsigned char dat[8];
  short x, y, z;  //形成补码
  ADXL345_readByte(0x32, dat, 6); //初始地址为0x32,连续读6个字节到dat[8]
  x = (dat[1] << 8) + dat[0];  //数据处理
  y = (dat[3] << 8) + dat[2];
  z = (dat[5] << 8) + dat[4];
  *out_X = float(x);  //数据处理
  *out_Y = float(y);
  *out_Z = float(z);
//  x = double(X) / 256;  //1g
//  y = double(Y) / 256;
//  z = double(Z) / 256;
//  x = double(X) * 3.9;  //mg
//  y = double(Y) * 3.9;
//  z = double(Z) * 3.9;
}

/* ADXL345初始化函数
 */
void adxl345::Init() {
  ADXL345_writeByte(DATA_FORMAT, 0x2B); //低电平中断输出,13位全分辨率,输出数据右对齐,16g量程
  ADXL345_writeByte(BW_RATE, 0x0A); //数据输出速度为100Hz
  ADXL345_writeByte(INT_ENABLE, 0x00);  //不使用中断
  ADXL345_writeByte(OFSX, 0x00);
  ADXL345_writeByte(OFSY, 0x00);
  ADXL345_writeByte(OFSZ, 0x00);
  ADXL345_writeByte(POWER_CTL, 0x28); //使能,测量模式
  delay(1000);
}

/* ADXL345写寄存器函数
 * addr为要写入数据的寄存器地址
 * data为要写入的数据
 */
void adxl345::ADXL345_writeByte(unsigned char addr, unsigned char data) {
  bool ack = 1; //用来判断应答
  //unsigned char cnt=0;
  do{
      IIC_Start();
      IIC_SendByte(slvAddr<<1); //第一次寻址不应答
      ack = IIC_RecvACK(); //应答
      //if((cnt++)>10) {Serial.println("error!"); return;}  //长时间寻不到址则打印"error"
  }while(ack); //如果不应答则继续寻址
  IIC_SendByte(addr); //写入寄存器地址
  ack = IIC_RecvACK();  //应答
  IIC_SendByte(data); //写入数据
  ack = IIC_RecvACK();  //应答
  IIC_Stop(); //停止信号
}

/* ADXL345连续读函数
 * addr为读数据初始地址
 * dat为数据指针
 * len为要读取的字节数
 */
void adxl345::ADXL345_readByte(unsigned char addr, unsigned char *dat, unsigned char len) {
  unsigned char i = 0;  //数据指针索引
  bool ack = 1; //用来判断应答
  do{
    IIC_Start(); //发送开始信号
    IIC_SendByte(slvAddr<<1); //IIC寻址,后续为写操作
    ack = IIC_RecvACK();  //应答
  }while(ack);  //如果不应答则继续寻址
  IIC_SendByte(addr); //写入寄存器地址
  ack = IIC_RecvACK();  //应答
  
  IIC_Start();  //发送开始信号
  IIC_SendByte((slvAddr<<1) | 0x01);  //IIC寻址,后续为读操作
  ack = IIC_RecvACK();  //应答

  while(--len){ //先读len-1个,发送应答信号
    dat[i] = IIC_RecvByte();  //读取字节
    IIC_SendACK(0); //发送应答信号
  //Serial.print(dat[i], HEX);
  //Serial.print(" ");
    i++;  //数据索引递增
  }
  dat[i] = IIC_RecvByte(); //读取字节
  IIC_SendACK(1); //发送非应答信号
  //Serial.print(dat[i], HEX);
  //Serial.println("  ");
  IIC_Stop(); //发送停止信号
}

/***I2C起始信号***/
void adxl345::IIC_Start() {
  digitalWrite(SDA, HIGH);
  delayMicroseconds(2);
  digitalWrite(SCL, HIGH); //拉高时钟线
  delayMicroseconds(2);  //延时2us
  digitalWrite(SDA, LOW);
  delayMicroseconds(2);
  digitalWrite(SCL, LOW);
  delayMicroseconds(2);
}

/*****I2C停止信号******/
void adxl345::IIC_Stop() {
  digitalWrite(SCL, LOW);  //拉低数据线
  delayMicroseconds(2);
  digitalWrite(SDA, LOW);  //拉低时钟线
  delayMicroseconds(2);    //延时2us
  digitalWrite(SCL, HIGH);
  delayMicroseconds(2);
  digitalWrite(SDA, HIGH);
  delayMicroseconds(2);
}

/**************************************
  发送应答信号
  入口参数:ack (0:ACK 1:NAK)
**************************************/
void adxl345::IIC_SendACK(bool ack) {
  digitalWrite(SDA, ack);   //写应答信号
  delayMicroseconds(2);
  digitalWrite(SCL, HIGH);  //拉高时钟线，等待读取应答信号
  delayMicroseconds(2);  //延时
  digitalWrite(SCL, LOW);   //拉低时钟线
  delayMicroseconds(2);   //延时
}

/**************************************
  接收应答信号
**************************************/
bool adxl345::IIC_RecvACK() {
  bool CY;
  digitalWrite(SCL, LOW);
  digitalWrite(SDA, HIGH); //释放总线
  pinMode(SDA, INPUT);  //这里要读取信号，所以数据线设置为INPUT
  digitalWrite(SCL, HIGH);
  delayMicroseconds(2);
  CY = digitalRead(SDA);
  digitalWrite(SCL, LOW);
  pinMode(SDA, OUTPUT);
  return CY;
}

/**************************************
  向IIC总线发送一个字节数据
**************************************/
void adxl345::IIC_SendByte(unsigned char dat) { //dat是要发送的一个字节的数据
  unsigned char i;
  for (i = 0; i < 8; i++) {  //高位开始传输
    digitalWrite(SCL, LOW);
    delayMicroseconds(2);
    if (0x80 & dat) digitalWrite(SDA, HIGH);  //置1
    else digitalWrite(SDA, LOW);  //置0
    dat <<= 1;
    delayMicroseconds(2);  //延时
    digitalWrite(SCL, HIGH);  //拉高时钟线 读取数据
    delayMicroseconds(2);
  }
}

/**************************************
  在IIC总线接收一个字节数据
**************************************/
unsigned char adxl345::IIC_RecvByte() {
  digitalWrite(SDA, HIGH); //释放总线
  unsigned char i;
  unsigned char dat = 0;    //dat是存放接收到的一个字节的数据
  pinMode(SDA, INPUT);  //这里要读取信号，所以数据线设置为INPUT
  for (i = 0; i < 8; i++) {
    digitalWrite(SCL, HIGH);
    delayMicroseconds(2);
    dat <<= 1;
    if (digitalRead(SDA)) dat++;
    delayMicroseconds(2);
    digitalWrite(SCL, LOW);
    delayMicroseconds(2);
  }
  pinMode(SDA, OUTPUT);
  return dat;
}