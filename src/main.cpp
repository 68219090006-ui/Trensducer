#include <Arduino.h>

<<<<<<< Updated upstream
const int ledPin = LED_BUILTIN;
const unsigned long blinkDelayMs = 500;

void setup() {
  pinMode(ledPin, OUTPUT);
=======
#ifndef LED_BUILTIN
#define LED_BUILTIN 2
#endif

const int ledPin = LED_BUILTIN;
const unsigned long blinkInterval = 500;

void setup() {
  Serial.begin(115200);
  pinMode(ledPin, OUTPUT);

  Serial.println("Blink test start");
>>>>>>> Stashed changes
}

void loop() {
  digitalWrite(ledPin, HIGH);
<<<<<<< Updated upstream
  delay(blinkDelayMs);

  digitalWrite(ledPin, LOW);
  delay(blinkDelayMs);
}
=======
  Serial.println("LED ON");
  delay(blinkInterval);

  digitalWrite(ledPin, LOW);
  Serial.println("LED OFF");
  delay(blinkInterval);
}
>>>>>>> Stashed changes
