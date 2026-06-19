#include <Arduino.h>

const int ledPin = LED_BUILTIN;
const unsigned long blinkDelayMs = 500;

void setup() {
  pinMode(ledPin, OUTPUT);
}

void loop() {
  digitalWrite(ledPin, HIGH);
  delay(blinkDelayMs);

  digitalWrite(ledPin, LOW);
  delay(blinkDelayMs);
}