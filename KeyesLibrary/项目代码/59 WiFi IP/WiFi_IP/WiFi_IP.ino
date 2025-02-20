/*
 * 名称   : WiFi IP
 * 功能   : 连接到路由器，读取WiFi对应的IP地址
 * 作者   : http://www.keyes-robot.com/ 
*/
#include "WiFiS3.h"
#include "arduino_secrets.h"

//请在 Secret 选项卡/arduino_secrets.h 中输入您的敏感数据
char ssid[] = "ChinaNet_2.4G";   // 您的网络 SSID(名称)
char pass[] = "ChinaNet@233";    // 您的网络密码(用于 WPA，或用作 WEP 密钥)
int keyIndex = 0;                // 您的网络密钥索引号(仅 WEP 需要)
int status = WL_IDLE_STATUS;
WiFiServer server(80);

void setup() {
  Serial.begin(9600);  // 初始化串口9600

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
}
