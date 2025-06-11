/*  
 * 名称   : MAX30102 HeartRate
 * 功能   : 读取MAX30102心率传感器检测的值
 * 作者   : http://www.keyes-robot.com/ 
*/
#include "MAX30105.h"
#include "heartRate.h"
MAX30105 particleSensor;
const byte RATE_SIZE = 4; //增加这个值以获得更平均的值, 数字4是好的.
byte rates[RATE_SIZE]; //心率阵列
byte rateSpot = 0;
long lastBeat = 0; //最后一心率发生的时间

float beatsPerMinute;
int beatAvg;

void setup()
{
  Serial.begin(115200);
  Serial.println("Initializing...");

  // 初始化传感器
  if (!particleSensor.begin(Wire, I2C_SPEED_FAST)) //使用默认I2C端口，400kHz速率
  {
    Serial.println("MAX30105 was not found. Please check wiring/power. ");
    while (1);
  }
  Serial.println("Place your index finger on the sensor with steady pressure.");

  particleSensor.setup(); //使用默认设置配置传感器
  particleSensor.setPulseAmplitudeRed(0x0A); //将红色LED转低，表示传感器正在运行
  particleSensor.setPulseAmplitudeGreen(0); //关闭绿色LED
}

void loop()
{
  long irValue = particleSensor.getIR();
  if (checkForBeat(irValue) == true)
  {
    //我们感觉到有心率节奏!
    long delta = millis() - lastBeat;
    lastBeat = millis();
    beatsPerMinute = 60 / (delta / 1000.0);
    if (beatsPerMinute < 255 && beatsPerMinute > 20)
    {
      rates[rateSpot++] = (byte)beatsPerMinute; //将读取的数据存储在数组中
      rateSpot %= RATE_SIZE; //打包变量

      //取读数平均值
      beatAvg = 0;
      for (byte x = 0 ; x < RATE_SIZE ; x++)
        beatAvg += rates[x];
      beatAvg /= RATE_SIZE;
    }
  }

  Serial.print("IR=");
  Serial.print(irValue);
  Serial.print(", BPM=");
  Serial.print(beatsPerMinute);
  Serial.print(", Avg BPM=");
  Serial.print(beatAvg);
  if (irValue < 50000)
    Serial.print(" No finger?");
    Serial.println();
    delay(20);
}
