/*  
 * 名称   : Photoresistor
 * 功能   : 读取光敏传感器的模拟值
 * 作者   : http://www.keyes-robot.com/ 
*/
int val = 0;   //设置value为0
int PIN_ANALOG_IN = A0;   //光敏传感器的引脚定义为A0

void setup() {
  Serial.begin(9600);   //波特率设置为9600
  pinMode(PIN_ANALOG_IN, INPUT);    //将传感器的引脚设置为输入模式
}

void loop() {
  val = analogRead(PIN_ANALOG_IN);    //读取传感器的模拟信号
  Serial.print("light_intensity:  ");    //打印字符串light_intensity:
  Serial.println(val);    //打印且显示光线强度的模拟信号
  delay(200);
}