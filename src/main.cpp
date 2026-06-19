#include <Arduino.h>

const int ledPin = LED_BUILTIN;
<<<<<<< Updated upstream
const unsigned long blinkDelayMs = 500;
=======
const unsigned long blinkInterval = 500;
>>>>>>> Stashed changes

void setup() {
  pinMode(ledPin, OUTPUT);
}

void loop() {
  digitalWrite(ledPin, HIGH);
<<<<<<< Updated upstream
  delay(blinkDelayMs);

  digitalWrite(ledPin, LOW);
  delay(blinkDelayMs);
=======
  delay(blinkInterval);

  digitalWrite(ledPin, LOW);
  delay(blinkInterval);
>>>>>>> Stashed changes
}