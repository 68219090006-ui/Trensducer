#include <Arduino.h>
#include <Wire.h>

// I2C address scanner
// ใช้ Serial Monitor ดูผล (ตั้งค่า baudrate ตามที่ตั้งไว้)

static uint8_t scanStart = 1;   // เริ่มสแกนที่ 0x01
static uint8_t scanEnd   = 0x7F; // สิ้นสุดที่ 0x7F

void setup() {
  Serial.begin(115200);
  while (!Serial) {
    delay(10);
  }

  Wire.begin();

  Serial.println();
  Serial.println(F("=== I2C Scanner ==="));
  Serial.println(F("Scanning..."));
}

void loop() {
  uint8_t foundCount = 0;

  for (uint8_t addr = scanStart; addr <= scanEnd; addr++) {
    Wire.beginTransmission(addr);
    uint8_t error = Wire.endTransmission();

    // error == 0 => device ACK
    if (error == 0) {
      Serial.print(F("Found I2C device at 0x"));
      if (addr < 16) Serial.print('0');
      Serial.print(addr, HEX);
      Serial.println();
      foundCount++;
    }
    delay(2);
  }

  if (foundCount == 0) {
    Serial.println(F("No I2C devices found"));
  }

  Serial.println(F("Done"));
  Serial.println();
  delay(2000);
}

