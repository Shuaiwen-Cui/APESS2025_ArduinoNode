/*  
 * 名称   : Joystick
 * 功能   : 从摇杆读取数据
 * 作者   : http://www.keyes-robot.com/ 
*/
int VRx = A3;  //定义X轴引脚
int VRy = A2;  //定义Y轴引脚
int SW = 7;    //定义Z轴引脚
int xPosition = 0;  //设置变量xPosition初始值为0
int yPosition = 0;  //设置变量yPosition初始值为0
int SW_state = 0;  //设置变量SW_state初始值为0

void setup() {
Serial.begin(9600); 
pinMode(VRx, INPUT);  //X轴引脚为输入模式
pinMode(VRy, INPUT);  //Y轴引脚为输入模式
pinMode(SW, INPUT_PULLUP);   //Z轴引脚为输入上拉模式
}

// 在loop()中，使用analogRead()读取X轴和Y轴的值
//并使用digitalRead()读取Z轴的值，然后显示它们。
void loop() {
  xPosition = analogRead(VRx); 
  yPosition = analogRead(VRy);
  SW_state = digitalRead(SW);
  Serial.print("X: ");
  Serial.print(xPosition);
  Serial.print(" | Y: ");
  Serial.print(yPosition);
  Serial.print(" | Button: ");
  Serial.println(SW_state);
  delay(100);
}