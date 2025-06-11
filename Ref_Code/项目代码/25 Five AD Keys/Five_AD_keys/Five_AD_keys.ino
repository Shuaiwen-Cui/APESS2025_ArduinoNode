/*  
 * 名称   : Five AD Keys
 * 功能   : 读取五路AD按键的值
 * 作者   : http://www.keyes-robot.com/ 
*/
int val = 0;
int ADkey = A0; //定义五路AD按键连接到A0

void setup() {
  Serial.begin(9600); //波特率设置为9600
}

void loop() {
  val = analogRead(ADkey);  //读取五路AD引脚的模拟值，并将其赋给变量val
  Serial.print(val);  //换行符输出变量val
  if (val <= 100) { //没有按下按钮时，Val小于或等于100
    Serial.println("   no key is pressed");
  } else if (val <= 300) { //当按下5键时，val在100到300之间
    Serial.println("   SW5 is pressed");
  } else if (val <= 500) { //当按下4键时，val在300到500之间
    Serial.println("   SW4 is pressed");
  } else if (val <= 700) { //当按下3键时，val在500到700之间
    Serial.println("   SW3 is pressed");
  } else if (val <= 900) { //当按下2键时，val在700到900之间
    Serial.println("   SW2 is pressed");
  } else {  //当按下1键时，val大于900
    Serial.println("   SW1 is pressed");
  }
  delay(50);
}