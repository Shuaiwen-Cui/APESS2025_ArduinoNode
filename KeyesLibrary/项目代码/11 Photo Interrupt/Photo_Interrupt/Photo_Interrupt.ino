/*
 * 名称   : Photo_Interrupt
 * 功能   : 光折断传感器计数
 * 作者   : http://www.keyes-robot.com/ 
*/
int PushCounter = 0;  //count变量的初始值为0
int State = 0;        //存储传感器当前的输出状态
int lastState = 0;    //存储传感器最后的输出状态
void setup() {
  Serial.begin(9600); //设置波特率为9600
  pinMode(3, INPUT);  //将光折断传感器引脚D3设置为输入模式
}

void loop() {
  State = digitalRead(3);   //读取当前状态
  if (State != lastState) { //如果状态与上次读取的不同
    if (State == 1) {       //遮挡光线时
      PushCounter = PushCounter + 1; //计数 + 1
      Serial.println(PushCounter);   //打印计数 
    }
  }
  lastState = State;  //更新状态
}