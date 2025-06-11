/*
 * 名称   : Relay
 * 功能   : 继电器开、关
 * 作者   : http://www.keyes-robot.com/ 
*/
#define Relay 3 //定义继电器的引脚为D3

void setup(){
  pinMode(Relay, OUTPUT); //设置“继电器”为“输出”
}

void loop(){
  digitalWrite(Relay, HIGH); //打开继电器
  delay(1000); //延迟1秒
  digitalWrite(Relay, LOW);  //关闭继电器
  delay(1000); //延迟1秒
}
