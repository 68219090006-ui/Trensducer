#include <Arduino.h>

<<<<<<< Updated upstream
const int ledPin = LED_BUILTIN;
const unsigned long blinkDelayMs = 500;

void setup() {
  pinMode(ledPin, OUTPUT);
}

void loop() {
  digitalWrite(ledPin, HIGH);
=======
const int led1Pin = 12;
const int led2Pin = 13;
const unsigned long blinkDelayMs = 500;

void setup() {
  pinMode(led1Pin, OUTPUT);
  pinMode(led2Pin, OUTPUT);
}

void loop() {
  digitalWrite(led1Pin, HIGH);
  digitalWrite(led2Pin, LOW);
>>>>>>> Stashed changes
  delay(blinkDelayMs);

  digitalWrite(led1Pin, LOW);
  digitalWrite(led2Pin, HIGH);
  delay(blinkDelayMs);
<<<<<<< Updated upstream
}
=======
}
>>>>>>> Stashed changes
