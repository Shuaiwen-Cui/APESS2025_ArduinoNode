/*  
 * 名称   : Flame Alarm
 * 功能   : 通过火焰传感器控制蜂鸣器
 * 作者   : http://www.keyes-robot.com/ 
*/
int item = 0;  //定义变量item初始值为0

void setup() {
  Serial.begin(9600);
  pinMode(A1, INPUT);  //火焰传感器数字引脚连接到A1
  pinMode(3, OUTPUT);  //蜂鸣器引脚连接D3
}

void loop() {
  item = analogRead(A1);  //读取火焰传感器的模拟信号并输出
  Serial.println(item);   //换行打印模拟信号
  if (item < 600) {  //火焰探测
    digitalWrite(3, HIGH);  //打开蜂鸣器
  } else {  //否则，请关闭蜂鸣器
    digitalWrite(3, LOW);
  }
  delay(100);  //延迟100毫秒
}