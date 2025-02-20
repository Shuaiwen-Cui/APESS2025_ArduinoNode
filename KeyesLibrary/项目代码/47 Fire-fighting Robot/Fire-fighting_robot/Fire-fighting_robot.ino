/*  
 * 名称   : Fire-fighting robot
 * 功能   : 火焰传感器控制130风扇模块
 * 作者   : http://www.keyes-robot.com/ 
*/
int item = 0;

void setup() {
  Serial.begin(9600);
  pinMode(A4, OUTPUT); //INA对应IN+，将A4设置为输出模式
  pinMode(A5, OUTPUT);//INB对应IN-，将A5置为输出模式
}

void loop() {
  item = analogRead(A1);//将火焰传感器连接到A1上，将模拟值读取到item
  Serial.print(item); //串口显示模拟值
  if (item < 300) {//300以下  
    Serial.print("   "); 
    Serial.println("Put out a fire");
    delay(100);
    digitalWrite(A4, LOW);//打开电风扇
    digitalWrite(A5, HIGH);
    
  } else {//否则，关闭风扇
    Serial.print("   "); 
    Serial.println("No flame detected");
    delay(100);
    digitalWrite(A4, LOW);
    digitalWrite(A5, LOW);
    
  } 
}
