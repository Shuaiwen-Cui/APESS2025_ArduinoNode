/*
 * 名称   : Tilt switch
 * 功能   : 读取倾斜传感器的值
 * 作者   : http://www.keyes-robot.com/ 
*/
int val; //定义一个变量val用来存储倾斜传感器输出的电平值

void setup() {
  Serial.begin(9600);
  pinMode(3, INPUT);  //将倾斜传感器的引脚连接到D3，设置为输入模式
}

void loop() {
  val = digitalRead(3); //读取模块电平信号
  Serial.println(val);  //打印倾斜传感器输出的电平值
  delay(100);   //延迟100毫秒
}