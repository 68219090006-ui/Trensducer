#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// KY-021 (Reed Switch)
// Wiring: S -> D7 (Arduino Uno)
static const int sensorPin = 7;



// LCD 16x2 แบบ I2C (ตาม design.md)
static const uint8_t lcdAddr = 0x27;

LiquidCrystal_I2C lcd(lcdAddr, 16, 2);

void setup() {
  Serial.begin(115200);

  Wire.begin();

  pinMode(sensorPin, INPUT);

  lcd.init();
  lcd.backlight();

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("KY-021 ready");
  lcd.setCursor(0, 1);
  lcd.print("Bring magnet");

  Serial.println(F("=== KY-021 + I2C LCD 16x2 ==="));
}

static const char* magnetStatusFromValue(int v) {
  // ตีความตามหลักทั่วไป: HIGH = Magnet detected
  return (v == HIGH) ? "Magnet" : "NoMag";
}

void loop() {
  // Debounce (กันสัญญาณ reed switch เด้ง/สั่น)
  const unsigned long debounceMs = 50; // ตามต้นแบบ 30–50ms

  static int lastRaw = LOW;
  static int stableState = LOW;
  static unsigned long lastChangeMs = 0;

  // event counter (นับจำนวนครั้งที่สถานะเปลี่ยนจริง)
  static unsigned long eventCount = 0;

  const int raw = digitalRead(sensorPin);

  if (raw != lastRaw) {
    lastRaw = raw;
    lastChangeMs = millis();
  }

  // ยอมรับว่า state เสถียรเมื่อ raw คงที่พอ
  if ((millis() - lastChangeMs) >= debounceMs && raw != stableState) {
    stableState = raw;
    eventCount++;

    const char* magnetText = magnetStatusFromValue(stableState);

    // Serial monitor: แสดง raw/stable + ข้อความ
    Serial.print(F("raw="));
    Serial.print(raw);
    Serial.print(F(" stable="));
    Serial.print(stableState);
    Serial.print(F(" -> "));
    Serial.print(magnetText);
    Serial.print(F(" | events="));
    Serial.println(eventCount);

    // LCD 16x2 (อัปเดตเฉพาะตอนสถานะเปลี่ยน)
    // บรรทัด 0: OPEN/CLOSED (ใช้ชื่อเดียวกับต้นแบบ)
    const bool isOpen = (stableState == HIGH); // เปลี่ยนค่าได้ถ้า HIGH/LOW กลับกัน
    lcd.setCursor(0, 0);
    if (isOpen) {
      lcd.print(F("OPEN           ")); // เติมให้เต็ม 16 ตัวอักษร
    } else {
      lcd.print(F("CLOSED         ")); // เติมให้เต็ม 16 ตัวอักษร
    }

    // บรรทัด 1: Count
    lcd.setCursor(0, 1);
    lcd.print(F("Count:"));
    // ช่องว่าง/ตัวเลขให้เต็ม 16 ตัวอักษร
    // Count: + space 6 ตำแหน่ง -> รวมให้ครบ 16 ด้วย padding
    unsigned long n = eventCount;
    // ลบข้อความเก่าให้หมดก่อนพิมพ์ตัวเลข
    lcd.print(F("      ")); // 6 ช่องว่าง
    lcd.setCursor(6, 1);
    lcd.print(n);
  }

  delay(5);
}





