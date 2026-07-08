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

    // Serial monitor: แสดงสถานะเป็น ON/OFF (ตามโจทย์)

    // Serial: แสดงสถานะเป็น ON/OFF (ตามโจทย์)
    const bool magnetDetected = (stableState == HIGH);
    Serial.print(F("Magnet="));
    Serial.print(magnetDetected ? F("ON") : F("OFF"));
    Serial.print(F(" raw="));
    Serial.print(raw);
    Serial.print(F(" stable="));
    Serial.print(stableState);
    Serial.print(F(" | events="));
    Serial.println(eventCount);


    // LCD 16x2 (อัปเดตเฉพาะตอนสถานะเปลี่ยน)
    // ตามที่กำหนด: ไม่แสดงสถานะ ON/OFF บนจอ LCD
    // แสดงเฉพาะ Count

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





