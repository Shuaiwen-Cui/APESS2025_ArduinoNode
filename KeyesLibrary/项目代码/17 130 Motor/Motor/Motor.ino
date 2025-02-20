/*
 * 名称   : 130DC Fan motor
 * 功能   : 电机顺、逆旋转
 * 作者   : http://www.keyes-robot.com/ 
*/
//定义电机的两个引脚接口，分别为A0和A1
int INA = A0;   //INA对应IN+
int INB = A1;  //INB对应IN-
void setup() {
  //将电机引脚设置为输出
  pinMode(INA, OUTPUT);
  pinMode(INB, OUTPUT);
}

void loop() {
  //逆时针方向转
  digitalWrite(INA, HIGH);
  digitalWrite(INB, LOW);
  delay(2000);
  //停止
  digitalWrite(INA, LOW);
  digitalWrite(INB, LOW);
  delay(1000);
  //顺时针方向转
  digitalWrite(INA, LOW);
  digitalWrite(INB, HIGH);
  delay(2000);
  //停止
  digitalWrite(INA, LOW);
  digitalWrite(INB, LOW);
  delay(1000);
}
