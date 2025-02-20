/*  
 * 名称   : Encoder
 * 功能   : 旋转编码器模块计数
 * 作者   : http://www.keyes-robot.com/ 
*/
int Encoder_CLK  = 2;  //定义旋转编码器的CLK引脚为D2
int Encoder_DT  = 3;   //定义旋转编码器的DT引脚为D3
int Encoder_Switch = 4;  //定义旋转编码器的SW引脚为D4 
 
int Encoder_Count;  //定义变量Encoder_Count
 
void setup() {
  Serial.begin(9600);   //设置波特率
  pinMode (Encoder_CLK, INPUT);   //设置旋转编码器的CLK引脚为输入模式
  pinMode (Encoder_DT, INPUT);    //设置旋转编码器的DT引脚为输入模式
  pinMode (Encoder_Switch, INPUT);  //设置旋转编码器的SW引脚为输入模式
}
 
int lastClk = HIGH;  //定义lastClk初始为HIGH

void loop() {
  int newClk = digitalRead(Encoder_CLK);  //读取编码器的Encoder_CLK值赋给newClk
  if (newClk != lastClk) {
    // 在CLK引脚上有一个变化
    lastClk = newClk;
    int dtValue = digitalRead(Encoder_DT);  //读取编码器的Encoder_DT值赋给dtValue
    if (newClk == LOW && dtValue == HIGH) {
      Encoder_Count ++;
      Serial.println(Encoder_Count);
    }
    if (newClk == LOW && dtValue == LOW) {
      Encoder_Count--;
      Serial.println(Encoder_Count);
    }
  }

  if (digitalRead(Encoder_Switch) == 0)
  {
    delay(5);
    if (digitalRead(Encoder_Switch) == 0) {
      Serial.println("Switch pressed");
      while (digitalRead(Encoder_Switch) == 0);
    }
  }
}