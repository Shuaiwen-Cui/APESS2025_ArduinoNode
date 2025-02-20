/*
 * 名称   : collision sensor
 * 功能   : 读取碰撞传感器的值
 * 作者   : http://www.keyes-robot.com/ 
*/
int val = 0;
void setup() {
  Serial.begin(9600);  //波特率设置为9600
  pinMode(3, INPUT);   //设置碰撞传感器的引脚D3为输入模式
}

void loop() {
  val = digitalRead(3);  //读取碰撞传感器的值
  Serial.print(val);      //打印碰撞传感器的值
  if (val == 0) {   //碰撞时的值为0
    Serial.print("        ");
    Serial.println("The end of this!");
    delay(100);
  }
  else {    //无碰撞时的值为1
    Serial.print("        ");
    Serial.println("All going well");
    delay(100);
  }
}
