/*
 * 名称   : Traffic_Light
 * 功能   : 模拟交通灯
 * 作者   : http://www.keyes-robot.com/ 
*/
int redPin = 2;      // 红色LED连接D2
int yellowPin = 3;   // 黄色LED连接到D3
int greenPin = 4;    // 绿色LED连接D4

void setup() {
  //LED接口设置为输出模式
  pinMode(greenPin, OUTPUT);
  pinMode(yellowPin, OUTPUT);
  pinMode(redPin, OUTPUT);
}

void loop() {
  digitalWrite(greenPin, HIGH);   //点亮绿色LED
  delay(5000);   //延迟5秒
  digitalWrite(greenPin, LOW);   //关闭绿色LED
  for (int i = 1; i <= 3; i = i + 1) {    //循环三次
    digitalWrite(yellowPin, HIGH);   //点亮黄色LED
    delay(500);   //延迟0.5秒
    digitalWrite(yellowPin, LOW);   //关闭黄色LED
    delay(500);   //延迟0.5秒
  }
  digitalWrite(redPin, HIGH);   //点亮红色LED
  delay(5000);  //延迟5秒
  digitalWrite(redPin, LOW);   //关闭红色LED
}
