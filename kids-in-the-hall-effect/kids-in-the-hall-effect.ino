#include <Arduino.h>
#include <TMAG5273.h>

// Define pins for the sensors
const int sensor1Pin = 2;
const int sensor2Pin = 3;

// Create instances of the TMAG5273 class
TMAG5273 sensor1;
TMAG5273 sensor2;

// Variables to store sensor readings
float magneticField1 = 0.0;
float magneticField2 = 0.0;

// Variables to store previous sensor readings
float prevMagneticField1 = 0.0;
float prevMagneticField2 = 0.0;

// Variables to store the direction of rotation
int direction = 0; // 1 for clockwise, -1 for counterclockwise

void setup() {
  Serial.begin(9600);

  // Initialize the sensors
  if (!sensor1.begin(sensor1Pin)) {
    Serial.println("Failed to initialize sensor 1!");
    while (1);
  }
  if (!sensor2.begin(sensor2Pin)) {
    Serial.println("Failed to initialize sensor 2!");
    while (1);
  }
}

void loop() {
  // Read magnetic field data from both sensors
  magneticField1 = sensor1.readMagneticField();
  magneticField2 = sensor2.readMagneticField();

  // Determine the direction of rotation
  if (magneticField1 > prevMagneticField1 && magneticField2 < prevMagneticField2) {
    direction = 1; // Clockwise
  } else if (magneticField1 < prevMagneticField1 && magneticField2 > prevMagneticField2) {
    direction = -1; // Counterclockwise
  }

  // Print the direction of rotation
  if (direction == 1) {
    Serial.println("Rotating clockwise");
  } else if (direction == -1) {
    Serial.println("Rotating counterclockwise");
  } else {
    Serial.println("No rotation detected");
  }

  // Update previous sensor readings
  prevMagneticField1 = magneticField1;
  prevMagneticField2 = magneticField2;

  // Small delay to avoid flooding the serial monitor
  delay(100);
}