#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// KY-021 (Reed Switch)
// ขา S ต่อ D2 (ตามเอกสาร)
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
  // ตีความตามที่ผู้ใช้อนุญาต: HIGH = Magnet detected
  return (v == HIGH) ? "Magnet detected" : "No magnet";
}

void loop() {
  int sensorValue = digitalRead(sensorPin);
  const char* msg = magnetStatusFromValue(sensorValue);

  // Serial
  Serial.print(F("sensor="));
  Serial.print(sensorValue);
  Serial.print(F(" -> "));
  Serial.println(msg);

  // LCD (สองบรรทัด)
  lcd.setCursor(0, 0);
  lcd.print("Magnet:");
  // เติมช่องว่างให้ลบเศษข้อความ
  lcd.print("       ");

  lcd.setCursor(0, 1);
  // แสดงข้อความให้พอดี 16 ตัวอักษร (ตัด/บวกเว้นว่างอัตโนมัติด้วยการพิมพ์ซ้ำ)
  lcd.print("                ");
  lcd.setCursor(0, 1);
  lcd.print(msg);

  delay(200);
}

