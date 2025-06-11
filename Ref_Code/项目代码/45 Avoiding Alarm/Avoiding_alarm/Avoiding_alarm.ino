/*  
 * 名称   : Avoiding alarm
 * 功能   : 避障传感器控制蜂鸣器
 * 作者   : http://www.keyes-robot.com/ 
*/
int item = 0;

void setup() {
  Serial.begin(9600);//启动串口监视器，设置波特率为9600
  pinMode(3, INPUT);  //避障传感器连接D3，设置为输入模式
  pinMode(5, OUTPUT); //将蜂鸣器连接到D5上并设置为输出模式
}

void loop() {
  item = digitalRead(3); //读取避障传感器输出的电平值
  Serial.println(item);  //打印变量item的值
  if (item == 0) {//检测到障碍物
    digitalWrite(5, HIGH);//蜂鸣器响起
  } else { //未检测到障碍物
    digitalWrite(5, LOW); //蜂鸣器关闭
  }
  delay(100);//延迟100ms
}