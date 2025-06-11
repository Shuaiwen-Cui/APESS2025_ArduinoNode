/*
 * 名称   : Laser sensor
 * 功能   : 激光灯闪光
 * 作者   : http://www.keyes-robot.com/ 
*/
int laserPin = 3;                //定义激光引脚为D3
void setup() {
  pinMode(laserPin, OUTPUT);     //将激光引脚定义为输出模式
}

void loop() {
  digitalWrite(laserPin, HIGH);     //打开激光
  delay(2000);                      //延迟2秒
  digitalWrite(laserPin, LOW);      //关闭激光
  delay(2000);                      //延迟2秒
}
