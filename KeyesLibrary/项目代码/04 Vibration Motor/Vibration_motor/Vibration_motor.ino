/*
 * 名称   : Vibration motor
 * 功能   : 震动马达
 * 作者   : http://www.keyes-robot.com/ 
*/
int Vibration_motor = 3;                //定义震动马达的引脚为D3
void setup() {
  pinMode(Vibration_motor, OUTPUT);     //将震动马达的引脚定义为输出模式
}

void loop() {
  digitalWrite(Vibration_motor, HIGH);     //震动马达
  delay(2000);                      //延迟2秒
  digitalWrite(Vibration_motor, LOW);      //不震动马达
  delay(2000);                      //延迟2秒
}
