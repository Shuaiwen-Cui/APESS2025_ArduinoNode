/*
 * 名称   : Hello World
 * 功能   : 输入字母“R”，串口显示“Hello World”。
 * 作者   : http://www.keyes-robot.com/ 
*/
char val;   // 定义变量val 

void setup(){
Serial.begin(9600);   // 设置波特率为9600
}

void loop(){
  if (Serial.available() > 0) {
    val=Serial.read();   // 读取指令或字符从PC到Arduino，并赋值给"val"的值
    if(val=='R') {   // 检查输入的字母是否为“R”,如果是
       Serial.println("Hello World!");  //显示“Hello World !”
    }
  }
}