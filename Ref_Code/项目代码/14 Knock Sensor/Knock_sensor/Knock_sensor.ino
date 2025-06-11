/*
 * 名称   : Knock sensor
 * 功能   : 读取敲击传感器的值
 * 作者   : http://www.keyes-robot.com/ 
*/
int val = 0;

void setup() {
  pinMode(5, INPUT);   //设置敲击传感器的引脚D5为输入模式
  pinMode(2, OUTPUT);  //设置交通灯模块上红色LED的引脚D2为输出模式
}

void loop() {
  val = digitalRead(5);  //读取敲击传感器的值
  if (val == 0) {   //敲击时的值为0
    digitalWrite(2, HIGH);  //红色LED亮
    delay(1000);
  }
  else {    //无敲击时的值为1
    digitalWrite(2, LOW);  //红色LED灭
  }
}
