/*  
 * 名称   : IR Receiver
 * 功能   : 解码红外线遥控器，通过串口打印出来
 * 作者   : http://www.keyes-robot.com/ 
*/
#include <IRremote.hpp>

#define IR_RECEIVE_PIN   3   // 定义红外接收模块引脚
IRrecv irrecv(IR_RECEIVE_PIN);     // 创建一个用于接收类的类对象
decode_results results;     // 创建一个解码结果类对象

void setup() {
  Serial.begin(9600);       // 初始化串口，波特率设置为9600
  IrReceiver.begin(IR_RECEIVE_PIN, ENABLE_LED_FEEDBACK);  // 启动接收器
}

void loop() {
  if (IrReceiver.decode()) {
      Serial.println(IrReceiver.decodedIRData.decodedRawData, HEX);  // 打印原始数据
      IrReceiver.printIRResultShort(&Serial); // 在一行中打印接收到的完整数据
      IrReceiver.printIRSendUsage(&Serial);  // 打印发送这些数据所需的语句
      IrReceiver.resume(); // 启用接收下一个值
  }
  delay(100);
}