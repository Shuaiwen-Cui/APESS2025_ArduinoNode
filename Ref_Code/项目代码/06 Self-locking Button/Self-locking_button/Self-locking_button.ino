/*
 * 名称   : Self-locking button
 * 功能   : 读自锁按键的值
 * 作者   : http://www.keyes-robot.com/ 
*/
int val = 0;            //用于存储自锁按键的键值
int button = 3;         //将自锁按键的引脚连接到D3
void setup() {
  Serial.begin(9600);      //启动串口监视器，设置波特率为9600
  pinMode(button, INPUT);  //设置自锁按键的引脚为输入模式
}

void loop() {
  val = digitalRead(button);  //读取自锁按键的值并将其赋值给变量val
  Serial.print(val);          //打印变量val的值
  if (val == 0) {             //按下自锁按键时读取到低电平，并打印出相关的信息
    Serial.print("        ");  
    Serial.println("Press the botton"); //打印自锁按键的释放信息
    delay(100);
  }

  else {               //按起自锁按键
    Serial.print("        ");
    Serial.println("Press the botton again");
    delay(100);
  }
}
