# รหัส68219090006 นาย ณัฐรณ เมืองพูล
## เทคนิคคอมพิวเตอร์

## การต่อใช้งาน LED 2 ตัว

### การต่อวงจร

- LED1 ต่อเข้าขา D12
- LED2 ต่อเข้าขา D13

ให้ต่อขา Anode (+) ของ LED แต่ละดวงเข้ากับขา D12 และ D13 ตามลำดับ และต่อขา Cathode (-) ลง GND ผ่านตัวต้านทาน 220-330 โอห์ม

### ตัวอย่างโค้ด

```cpp
const int LED1 = 12;
const int LED2 = 13;

void setup() {
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
}

void loop() {
  digitalWrite(LED1, HIGH);
  digitalWrite(LED2, LOW);
  delay(500);

  digitalWrite(LED1, LOW);
  digitalWrite(LED2, HIGH);
  delay(500);
}
```

### ผลลัพธ์

LED ทั้ง 2 ตัวจะสลับกันติดและดับ ทำให้เห็นไฟกระพริบ