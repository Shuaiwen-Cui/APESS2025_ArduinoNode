/*
 * 名称   : WiFi Web Page Control  
 * 功能   : WIFI 网页控制多个传感器模块
 * 作者   : http://www.keyes-robot.com/ 
*/
#include "WiFiS3.h"
#include "arduino_secrets.h" 
#include <Servo.h>
#include <FastLED.h>

//请在 Secret 选项卡/arduino_secrets.h 中输入您的敏感数据
char ssid[] = "ChinaNet_2.4G";   // 您的网络 SSID(名称)
char pass[] = "ChinaNet@233";    // 您的网络密码(用于 WPA，或用作 WEP 密钥)
int keyIndex = 0;                // 您的网络密钥索引号(仅 WEP 需要)
int val = 0;

#define NUM_LEDS 4   //定义SK6812 RGB模块上LED灯珠数量
#define LED_PIN  12   //定义SK6812 RGB模块控制引脚为D12
CRGB leds[NUM_LEDS];

int Active_Buzzer = 3;   //定义有源蜂鸣器引脚为D3
int Passive_Buzzer = 5;   //定义8002b功放喇叭模块引脚为D5
int INA = A4;  //定义电机模块的IN+(INA)引脚为A4
int INB = A5;  //定义电机模块的IN-(INB)引脚为A5
int servoPin = A1;  // 定义舵机引脚A1
Servo myservo;  //创建舵机对象来控制舵机

int status = WL_IDLE_STATUS;
WiFiServer server(80);

void setup() {
  Serial.begin(9600);      // 初始化串口9600
  pinMode(LED_PIN, OUTPUT);      // 设置SK6812 RGB模块引脚为输出模式
  pinMode(INA, OUTPUT);      // 设置电机模块的IN+(INA)引脚为输出模式
  pinMode(INB, OUTPUT);      // 设置电机模块的IN-(INB)引脚为输出模式
  pinMode(Active_Buzzer, OUTPUT);      // 设置有源蜂鸣器引脚为输出模式
  pinMode(Passive_Buzzer, OUTPUT);      // 设置8002b功放喇叭模块引脚为输出模式
  myservo.attach(servoPin);  //选择舵机引脚A1
  myservo.write(0); //旋转到0度
  delay(1000); //延迟1s
  FastLED.addLeds<WS2812B, LED_PIN, GRB>(leds, NUM_LEDS);
  FastLED.setBrightness(50);   //设置SK6812 RGB的亮度

  // 检查 WiFi 模块:
  if (WiFi.status() == WL_NO_MODULE) {
    Serial.println("Communication with WiFi module failed!");
    // 不继续
    while (true);
  }

  String fv = WiFi.firmwareVersion();
  if (fv < WIFI_FIRMWARE_LATEST_VERSION) {
    Serial.println("Please upgrade the firmware");
  }

  // 尝试连接WiFi网络:
  while (status != WL_CONNECTED) {
    Serial.print("Attempting to connect to Network named: ");
    Serial.println(ssid);                   // 打印网络名称(SSID)

    // 连接到WPA/WPA2网络，如果使用open或WEP网络，请更改此行:
    status = WiFi.begin(ssid, pass);
    // 等待10秒连接:
    delay(10000);
  }
  server.begin();                           // 在端口80上启动web服务器
  printWifiStatus();                        // 你现在已经连接上了，所以打印出状态
}


void loop() {
  WiFiClient client = server.available();   // 实时监听即将到来的客户端

  if (client) {                             // 如果你监听到客户端的话,
    Serial.println("new client");           // 在串口上打印一条消息
    String currentLine = "";                // 创建一个字符串来保存从客户端传入的数据
    while (client.connected()) {            // 在客户端连接时循环
      if (client.available()) {             // 如果有字节需要从客户端读取,
        char c = client.read();             // 读取一个字节，然后
        Serial.write(c);                    // 打印到串行监视器上
        if (c == '\n') {                    // 如果字节是换行符

          // 如果当前行为空，则一行中有两个换行符.
          // 这是客户端HTTP请求的结束，因此发送一个响应:
          if (currentLine.length() == 0) {
            // HTTP首部总是以响应代码开始 (e.g. HTTP/1.1 200 OK)
            // 以及一个内容类型，以便客户端知道将要发生什么，然后是一个空行:
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println();

            // HTTP响应的内容跟在首部之后:
            client.print("<p style=\"font-size:7vw;\">Click <a href=\"/A\">here</a> turn on RGB<br></p>");
            client.print("<p style=\"font-size:7vw;\">Click <a href=\"/B\">here</a> turn off RGB<br></p>");
            client.print("<p style=\"font-size:7vw;\">Click <a href=\"/C\">here</a> turn on fan<br></p>");
            client.print("<p style=\"font-size:7vw;\">Click <a href=\"/D\">here</a> turn off fan<br></p>");
            client.print("<p style=\"font-size:7vw;\">Click <a href=\"/E\">here</a> play music<br></p>");
            client.print("<p style=\"font-size:7vw;\">Click <a href=\"/F\">here</a> turn on buzzer<br></p>");
            client.print("<p style=\"font-size:7vw;\">Click <a href=\"/G\">here</a> turn off buzzer<br></p>");
            client.print("<p style=\"font-size:7vw;\">Click <a href=\"/H\">here</a> <br>servo turn to 180</p>");
            client.print("<p style=\"font-size:7vw;\">Click <a href=\"/I\">here</a> <br>servo turn to 0</p>");
           
            // HTTP响应以另一个空行结束:
            client.println();
            // 跳出while循环:
            break;
          } else {    // 如果有换行符，清除currentLine:
            currentLine = "";
          }
        } else if (c != '\r') {  // 如果你有除回车字符以外的其他字符,
          currentLine += c;      // 并且将其添加到currentLine的末尾
        }

        // 检查客户端请求是否存在 "GET /A"or"GET /B"or"GET /C"or"GET /D"or"GET /E"or"GET /F"or"GET /G"or"GET /H"or"GET /I":
        if (currentLine.endsWith("GET /A")) {    // GET /A 打开RGB LED
          rgb_led();       
        }
        if (currentLine.endsWith("GET /B")) {    // GET /B 关闭RGB LED
          fill_solid(leds, NUM_LEDS, CRGB::Black);  
          FastLED.show(); 
        }
        if (currentLine.endsWith("GET /C")) {  // GET /C 电机模块转动
          digitalWrite(INA, LOW);                
          analogWrite(INB, 100);
        }
        if (currentLine.endsWith("GET /D")) {  // GET /D 电机模块不转
          digitalWrite(INA, LOW);               
          analogWrite(INB, 0);
        }
        if (currentLine.endsWith("GET /E")) {  // GET /E 8002b功放喇叭模块演奏音乐
          music();                               
        }
        if (currentLine.endsWith("GET /F")) {  // GET /F 有源蜂鸣器鸣叫
          digitalWrite(Active_Buzzer, HIGH);            
        }
        if (currentLine.endsWith("GET /G")) {  // GET /G 有源蜂鸣器不响
          digitalWrite(Active_Buzzer, LOW);             
        }
        if (currentLine.endsWith("GET /H")) {  // GET /H 舵机转到180°
          myservo.write(180); //旋转到180度
          delay(1000); //延迟1s
        }
        if (currentLine.endsWith("GET /I")) {  // GET /I 舵机转到0°
          myservo.write(0); //旋转到0度
          delay(1000); //延迟1s
        }
      } 
    }
    // 断开连接:
    client.stop();
    Serial.println("client disconnected");
  }
}

void printWifiStatus() {
  // 打印你所连接的网络的SSID:
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  // 打印主控板接收到的IP地址:
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);

  // 打印接收到的信号强度:
  long rssi = WiFi.RSSI();
  Serial.print("signal strength (RSSI):");
  Serial.print(rssi);
  Serial.println(" dBm");
  
  // 在浏览器中打开http://[ip]:
  Serial.print("To see this page in action, open a browser to http://");
  Serial.println(ip);
}

void music() {
  #define NOTE_B0  31
  #define NOTE_C1  33
  #define NOTE_CS1 35
  #define NOTE_D1  37
  #define NOTE_DS1 39
  #define NOTE_E1  41
  #define NOTE_F1  44
  #define NOTE_FS1 46
  #define NOTE_G1  49
  #define NOTE_GS1 52
  #define NOTE_A1  55
  #define NOTE_AS1 58
  #define NOTE_B1  62
  #define NOTE_C2  65
  #define NOTE_CS2 69
  #define NOTE_D2  73
  #define NOTE_DS2 78
  #define NOTE_E2  82
  #define NOTE_F2  87
  #define NOTE_FS2 93
  #define NOTE_G2  98
  #define NOTE_GS2 104
  #define NOTE_A2  110
  #define NOTE_AS2 117
  #define NOTE_B2  123
  #define NOTE_C3  131
  #define NOTE_CS3 139
  #define NOTE_D3  147
  #define NOTE_DS3 156
  #define NOTE_E3  165
  #define NOTE_F3  175
  #define NOTE_FS3 185
  #define NOTE_G3  196
  #define NOTE_GS3 208
  #define NOTE_A3  220
  #define NOTE_AS3 233
  #define NOTE_B3  247
  #define NOTE_C4  262
  #define NOTE_CS4 277
  #define NOTE_D4  294
  #define NOTE_DS4 311
  #define NOTE_E4  330
  #define NOTE_F4  349
  #define NOTE_FS4 370
  #define NOTE_G4  392
  #define NOTE_GS4 415
  #define NOTE_A4  440
  #define NOTE_AS4 466
  #define NOTE_B4  494
  #define NOTE_C5  523
  #define NOTE_CS5 554
  #define NOTE_D5  587
  #define NOTE_DS5 622
  #define NOTE_E5  659
  #define NOTE_F5  698
  #define NOTE_FS5 740
  #define NOTE_G5  784
  #define NOTE_GS5 831
  #define NOTE_A5  880
  #define NOTE_AS5 932
  #define NOTE_B5  988
  #define NOTE_C6  1047
  #define NOTE_CS6 1109
  #define NOTE_D6  1175
  #define NOTE_DS6 1245
  #define NOTE_E6  1319
  #define NOTE_F6  1397
  #define NOTE_FS6 1480
  #define NOTE_G6  1568
  #define NOTE_GS6 1661
  #define NOTE_A6  1760
  #define NOTE_AS6 1865
  #define NOTE_B6  1976
  #define NOTE_C7  2093
  #define NOTE_CS7 2217
  #define NOTE_D7  2349
  #define NOTE_DS7 2489
  #define NOTE_E7  2637
  #define NOTE_F7  2794
  #define NOTE_FS7 2960
  #define NOTE_G7  3136
  #define NOTE_GS7 3322
  #define NOTE_A7  3520
  #define NOTE_AS7 3729
  #define NOTE_B7  3951
  #define NOTE_C8  4186
  #define NOTE_CS8 4435
  #define NOTE_D8  4699
  #define NOTE_DS8 4978
  #define REST 0

  int tempo=114; // 改变这个可使歌曲变慢或变快
  // 乐曲的音符后面跟着持续时间.
  // A 4表示四分音符，8表示十八分音符，16表示十六分音符，以此类推
  // !!负数用来表示带点的注释
  // 所以-4意味着一个带点的四分音符，也就是说，四分之一加上十八分之一
  int melody[] = {
    NOTE_E4,4,  NOTE_E4,4,  NOTE_F4,4,  NOTE_G4,4,//1
    NOTE_G4,4,  NOTE_F4,4,  NOTE_E4,4,  NOTE_D4,4,
    NOTE_C4,4,  NOTE_C4,4,  NOTE_D4,4,  NOTE_E4,4,
    NOTE_E4,-4, NOTE_D4,8,  NOTE_D4,2,
    NOTE_E4,4,  NOTE_E4,4,  NOTE_F4,4,  NOTE_G4,4,//4
    NOTE_G4,4,  NOTE_F4,4,  NOTE_E4,4,  NOTE_D4,4,
    NOTE_C4,4,  NOTE_C4,4,  NOTE_D4,4,  NOTE_E4,4,
    NOTE_D4,-4,  NOTE_C4,8,  NOTE_C4,2,
    NOTE_D4,4,  NOTE_D4,4,  NOTE_E4,4,  NOTE_C4,4,//8
    NOTE_D4,4,  NOTE_E4,8,  NOTE_F4,8,  NOTE_E4,4, NOTE_C4,4,
    NOTE_D4,4,  NOTE_E4,8,  NOTE_F4,8,  NOTE_E4,4, NOTE_D4,4,
    NOTE_C4,4,  NOTE_D4,4,  NOTE_G3,2,
    NOTE_E4,4,  NOTE_E4,4,  NOTE_F4,4,  NOTE_G4,4,//12
    NOTE_G4,4,  NOTE_F4,4,  NOTE_E4,4,  NOTE_D4,4,
    NOTE_C4,4,  NOTE_C4,4,  NOTE_D4,4,  NOTE_E4,4,
    NOTE_D4,-4,  NOTE_C4,8,  NOTE_C4,2
  };
  // 给出字节数的类型，每个int值由两个字节(16位)组成
  // 每个音符有两个值(音高和持续时间)，所以每个音符有四个字节
  int notes=sizeof(melody)/sizeof(melody[0])/2; 
  // 这计算了整个音符的持续时间，单位是ms (60s/节拍)*4拍
  int wholenote = (60000 * 4) / tempo;
  int divider = 0, noteDuration = 0;

  // 重复旋律的音符
  // 记住，数组是音符数的两倍(音符+持续时间)
  for (int thisNote = 0; thisNote < notes * 2; thisNote = thisNote + 2) {
    // 计算每个音的持续时间
    divider = melody[thisNote + 1];
    if (divider > 0) {
    noteDuration = (wholenote) / divider; // 常规提示，继续
    } else if (divider < 0) {
      // 虚线注释的持续时间为负
       noteDuration = (wholenote) / abs(divider);
       noteDuration *= 1.5; // 给打点音符增加一半的持续时间
    }
    // 只在90%的时间里演奏这个音符，留下10%作为暂停
    tone(Passive_Buzzer, melody[thisNote], noteDuration*0.9);
  // 等待特定的时间后再演奏下一个音符.
    delay(noteDuration);
     noTone(Passive_Buzzer);  // 下一个音节前停止波形产生前的下一个说明.
  }
}

void rgb_led(){ 
  fill_solid(leds, NUM_LEDS, CRGB::Red);  // SK6812 RGB模块4个LED灯珠亮红色灯
  FastLED.show();
  delay(500);
  fill_solid(leds, NUM_LEDS, CRGB::Green);  // SK6812 RGB模块4个LED灯珠亮绿色灯
  FastLED.show();
  delay(500);
  fill_solid(leds, NUM_LEDS, CRGB::Blue);  // SK6812 RGB模块4个LED灯珠亮蓝色灯
  FastLED.show();
  delay(500);
  fill_solid(leds, NUM_LEDS, CRGB::Orange);  // SK6812 RGB模块4个LED灯珠亮橙色灯
  FastLED.show();
  delay(500);
  fill_solid(leds, NUM_LEDS, CRGB::Yellow);  // SK6812 RGB模块4个LED灯珠亮黄色灯
  FastLED.show();
  delay(500);
  fill_solid(leds, NUM_LEDS, CRGB::Purple);  // SK6812 RGB模块4个LED灯珠亮紫色灯
  FastLED.show();
  delay(500);
  fill_solid(leds, NUM_LEDS, CRGB::Gold);  // SK6812 RGB模块4个LED灯珠亮金色灯
  FastLED.show();
  delay(500);
  fill_solid(leds, NUM_LEDS, CRGB::Pink);  // SK6812 RGB模块4个LED灯珠亮粉红色灯
  FastLED.show();
  delay(500);
  fill_solid(leds, NUM_LEDS, CRGB::Magenta);  // SK6812 RGB模块4个LED灯珠亮品红色灯
  FastLED.show();
  delay(500);
  fill_solid(leds, NUM_LEDS, CRGB::White);   // SK6812 RGB模块4个LED灯珠亮白灯
  FastLED.show();
  delay(500);
}
