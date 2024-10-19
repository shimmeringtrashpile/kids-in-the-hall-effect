#include <Arduino.h>

const int latchPin = 2; // US1881 Non-Latching Hall effect sensor pin
const int hallPin = 3; // AH1815 Latching Hall effect sensor pin
const int ledPin = 13; // Built-in LED pin
int latchState = LOW; // Hall effect sensor state
int hallState = LOW; // Hall effect sensor state


void setup() {
  // put your setup code here, to run once:
  // set the hallPin as an input
  pinMode(latchPin, INPUT);
  pinMode(hallPin, INPUT);
  pinMode(ledPin, OUTPUT);
  
  // turn on the internal pull-up resistors
  // digitalWrite(hallPin, HIGH);
  // digitalWrite(latchPin, HIGH);

  // initialize the serial communication
  Serial.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly:
  latchState = digitalRead(latchPin);
  hallState = digitalRead(hallPin);

  if (latchState == HIGH) {
    // turn on the LED
    digitalWrite(ledPin, HIGH);
    Serial.println("Magnet on Latching!");
  } else if (hallState == LOW) { // The US1881 is open drain. LOW when magnet passes.
    // turn on the LED
    digitalWrite(ledPin, HIGH);
    Serial.println("Magnet on Hall!");
  } else {
    // turn off the LED
    digitalWrite(ledPin, LOW);
    Serial.println("No!");
  }
}
