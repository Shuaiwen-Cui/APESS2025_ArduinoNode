/*
 * 名称   : line tracking
 * 功能   : 读取循迹传感器值
 * 作者   : http://www.keyes-robot.com/ 
*/
int val = 0;
void setup() {
  Serial.begin(9600); //设置波特率为9600
  pinMode(3, INPUT);  //将传感器引脚D3设置为输入模式
}

void loop() {
  val = digitalRead(3);   //读取循迹传感器的数字电平输出
  Serial.print(val);      //打印循迹传感器的读取到的数字电平的值
  if (val == 0) {  //检测到白色物体的值为0
    Serial.print("        ");
    Serial.println("White");
    delay(100);
  }
  else {  //检测到黑色物体的值为1
    Serial.print("        ");
    Serial.println("Black");
    delay(100);
  }
}
