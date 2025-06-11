/*  
 * 名称   : MicroPhone
 * 功能   : 读取声音传感器的模拟值
 * 作者   : http://www.keyes-robot.com/ 
*/
int val = 0;   //设置value为0
int PIN_ANALOG_IN = A0;   //声音传感器的引脚定义为A0

void setup() {
  Serial.begin(9600);   //波特率设置为9600
  pinMode(PIN_ANALOG_IN, INPUT);    //将传感器的引脚设置为输入模式
}

void loop() {
  val = analogRead(PIN_ANALOG_IN);    //读取传感器的模拟信号
  Serial.print("sound volume:  ");    //打印字符串sound volume:
  Serial.println(val);    //打印且显示声音强度的模拟信号
  delay(200);
}
