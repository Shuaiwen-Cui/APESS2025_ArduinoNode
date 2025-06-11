/*
 * 名称   : Touch sensor
 * 功能   : 读取电容触摸传感器的值
 * 作者   : http://www.keyes-robot.com/ 
*/
int val = 0;
int touch = 3;            //定义触摸引脚D3 
void setup() {
  Serial.begin(9600);     //波特率为9600
  pinMode(touch, INPUT);  //设置触摸引脚为输入模式
}

void loop() {
  val = digitalRead(touch); //读取触摸引脚的值
  Serial.print(val);        //打印触摸引脚的值
  if (val == 1) {  //按下为高电平
    Serial.print("        ");
    Serial.println("Touch the button");
    delay(100);
  }
  else {          //释放为低电平
    Serial.print("        ");
    Serial.println("Loosen the button");
    delay(100);
  }
}
