#include <Arduino.h> // <-- เพิ่มบรรทัดนี้ที่บรรทัดแรกสุดเพื่อแก้ Error ครับ

/**
 * โปรแกรมทดสอบโมดูลสวิตช์แม่เหล็ก KY-021 Mini Reed Switch (เวอร์ชันสำหรับ PlatformIO)
 * มีระบบป้องกันสัญญาณรบกวน (Debounce) และแสดงผลผ่าน Serial Monitor
 */

// กำหนดขา Digital Pin ที่ต่อกับขา Signal (S) ของเซ็นเซอร์ KY-021 [cite: 9]
const int REED_PIN = 2; 

// ตัวแปรสำหรับเก็บสถานะของเซ็นเซอร์
int lastReedState = HIGH;   // สถานะก่อนหน้า (ปกติสวิตช์จะ ON/HIGH ค้างไว้) [cite: 14]
int currentReedState;       // สถานะปัจจุบันที่กรองสัญญาณรบกวนแล้ว

// ตัวแปรสำหรับจัดการ Debounce (ป้องกันสัญญาณแกว่ง)
unsigned long lastDebounceTime = 0;  
const unsigned long DEBOUNCE_DELAY = 50; // หน่วงเวลาตรวจสอบ 50 มิลลิวินาที

void setup() {
  // เริ่มต้น Serial Monitor ที่ความเร็ว 9600 bps
  Serial.begin(9600);
  
  // กำหนดให้ขา REED_PIN เป็นอินพุต (INPUT) เพื่อรับค่าดิจิทัล [cite: 24]
  pinMode(REED_PIN, INPUT);
  
  Serial.println("=========================================");
  Serial.println("   ระบบตรวจสอบเซ็นเซอร์ KY-021 เริ่มทำงาน   ");
  Serial.println("=========================================");
}

void loop() {
  // 1. อ่านค่าดิบจากเซ็นเซอร์ (Raw Read)
  int reading = digitalRead(REED_PIN);

  // 2. ตรวจสอบว่าค่าที่อ่านได้เปลี่ยนไปจากเดิมไหม
  if (reading != lastReedState) {
    // รีเซ็ตเวลาเริ่มต้นของสัญญาณรบกวน
    lastDebounceTime = millis();
  }

  // 3. ถ้าสัญญาณนิ่งนานเกินกว่าค่า DEBOUNCE_DELAY ที่ตั้งไว้ ถือว่าเป็นสถานะที่แท้จริง
  if ((millis() - lastDebounceTime) > DEBOUNCE_DELAY) {
    
    // ถ้าสถานะเปลี่ยนไปจากเดิมจริงๆ ให้ทำงานในเงื่อนไขนี้
    if (reading != currentReedState) {
      currentReedState = reading;

      // 4. แสดงผลลัพธ์ตามสถานะที่แท้จริง
      if (currentReedState == HIGH) {
        Serial.println("[STATUS] ปกติ: ไม่พบสนามแม่เหล็ก");
      } else {
        Serial.println("[STATUS] แจ้งเตือน: *** ตรวจพบสนามแม่เหล็ก! ***"); // [cite: 14]
      }
    }
  }

  // บันทึกค่าการอ่านครั้งนี้เพื่อเอาไปเปรียบเทียบในรอบถัดไป
  lastReedState = reading;
}