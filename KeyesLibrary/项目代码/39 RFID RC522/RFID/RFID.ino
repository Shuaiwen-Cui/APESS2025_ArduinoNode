/*  
 * 名称   : RFID
 * 功能   : RFID读取器UID
 * 作者   : http://www.keyes-robot.com/ 
*/
#include "MFRC522_I2C_SOFT.h"

// 0x28是SDA上的i2c地址。如果不匹配，请用i2cscanner检查您的地址.
MFRC522 mfrc522(0x28, A4, A5);   // 创建MFRC522实例.

void setup() {
  Serial.begin(115200);           // 初始化与PC的串行通信
  mfrc522.PCD_Init();             // 初始化 MFRC522
  ShowReaderDetails();            // 显示详细的PCD - MFRC522读卡器细节
  Serial.println(F("Scan PICC to see UID, type, and data blocks..."));
}

void loop() {
  // 寻找新的卡片，如果有的话选择一张
  if ( ! mfrc522.PICC_IsNewCardPresent() || ! mfrc522.PICC_ReadCardSerial() ) {
    delay(50);
    return;
  }
  
  // 选择一张门卡，UID和SAK分别为mfrc522.uid  
  // 保存UID
  Serial.print(F("Card UID:"));
  for (byte i = 0; i < mfrc522.uid.size; i++) {
    Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
    Serial.print(mfrc522.uid.uidByte[i], HEX);
  } 
  Serial.println();
}

void ShowReaderDetails() {
  // 获得MFRC522软件
  byte v = mfrc522.PCD_ReadRegister(mfrc522.VersionReg);
  Serial.print(F("MFRC522 Software Version: 0x"));
  Serial.print(v, HEX);
  if (v == 0x91)
    Serial.print(F(" = v1.0"));
  else if (v == 0x92)
    Serial.print(F(" = v2.0"));
  else
    Serial.print(F(" (unknown)"));
  Serial.println("");
  // 返回0x00或0xFF时，可能是通信信号传输失败
  if ((v == 0x00) || (v == 0xFF)) {
    Serial.println(F("WARNING: Communication failure, is the MFRC522 properly connected?"));
  }
}

