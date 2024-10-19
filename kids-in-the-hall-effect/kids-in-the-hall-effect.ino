#include <Wire.h>               // Used to establish serial communication on the I2C bus
#include "SparkFun_TMAG5273_Arduino_Library.h"  // Used to send and receive specific information from our sensor

TMAG5273 sensor1;  // Initialize first hall-effect sensor
TMAG5273 sensor2;  // Initialize second hall-effect sensor

// I2C addresses for the sensors
uint8_t i2cAddress1 = TMAG5273_I2C_ADDRESS_INITIAL;
uint8_t i2cAddress2 = 0X23; // Assuming an alternate address for the second sensor

// Interrupt pins used
uint8_t intPin1 = 2;
uint8_t intPin2 = 3;

// Start the flags as false
bool interruptFlag1 = false;
bool interruptFlag2 = false;

// ISR to print what interrupt was triggered for sensor 1
void isr1() 
{
  interruptFlag1 = true;
}

// ISR to print what interrupt was triggered for sensor 2
void isr2() 
{
  interruptFlag2 = true;
}

void setup() 
{
  Wire.begin();
  // Start serial communication at 115200 baud
  Serial.begin(115200);

  // Initialize the first sensor
  if (!sensor1.begin(i2cAddress1)) {
    Serial.println("Failed to initialize sensor 1!");
    while (1);
  }

  // Initialize the second sensor
  if (!sensor2.begin(i2cAddress2)) {
    Serial.println("Failed to initialize sensor 2!");
    while (1);
  }

  // Attach interrupts
  pinMode(intPin1, INPUT);
  // Attach interrupt to pin 4 as a digital, falling pin
  attachInterrupt(digitalPinToInterrupt(intPin1), isr1, CHANGE);

  pinMode(intPin2, INPUT);
  // Attach interrupt to pin 4 as a digital, falling pin
  attachInterrupt(digitalPinToInterrupt(intPin2), isr2, CHANGE);

  // Begin example of the magnetic sensor code (and add whitespace for easy reading)
  Serial.println("Two TMAG5273 Boards!: Interrupts");
  Serial.println("");

  // If begin is successful (0), then start example
  if (sensor1.begin(i2cAddress1, Wire) == true)
  {
    Serial.println("Sensor 1 Begin");
  } 
  else  // Otherwise, infinite loop
  {
    Serial.println("Sensor 1 failed to setup - Freezing code.");
    while (1);  // Runs forever
  }

    // If begin is successful (0), then start example
  if (sensor2.begin(i2cAddress2, Wire) == true)
  {
    Serial.println("Sensor 2 Begin");
  } 
  else  // Otherwise, infinite loop
  {
    Serial.println("Sensor 2 failed to setup - Freezing code.");
    while (1);  // Runs forever
  }
  
  // Set interrupt through !INT
  sensor1.setInterruptMode(TMAG5273_INTERRUPT_THROUGH_INT);
  sensor2.setInterruptMode(TMAG5273_INTERRUPT_THROUGH_INT);

  // Set the !INT pin state - pulse for 10us
  sensor1.setIntPinState(true);
  sensor2.setIntPinState(true);

  // Enable the interrupt response for the thresholds
  sensor1.setThresholdEn(true);
  sensor2.setThresholdEn(true);

  //int pinStatus = sensor.getInterruptPinStatus();
  pinMode(intPin1, INPUT);
  pinMode(intPin2, INPUT);

  // Set X, Y, Z, and T Thresholds for interrupt to be triggered
  sensor1.setXThreshold(5);            // mT
  //sensor.setYThreshold(5);            // mT
  //sensor.setZThreshold(5);            // mT
  //sensor.setTemperatureThreshold(50);  // C

  // Set X, Y, Z, and T Thresholds for interrupt to be triggered
  sensor2.setXThreshold(5);            // mT
  //sensor.setYThreshold(5);            // mT
  //sensor.setZThreshold(5);            // mT
  //sensor.setTemperatureThreshold(50);  // C

  Serial.print("Sensor 1 X Threshold Set: ");
  Serial.println(sensor1.getXThreshold());

  Serial.print("Sensor 2 X Threshold Set: ");
  Serial.println(sensor2.getXThreshold());


}

/* To use the other thresholds, simply change the names and use the other functions: 
- sensor1.getYThreshold();
- sensor1.getZThreshold();
- sensor1.getTemperatureThreshold();

- sensor2.getYThreshold();
- sensor2.getZThreshold();
- sensor2.getTemperatureThreshold();
*/

void loop() {
  if (interruptFlag1 == true) 
  {
    interruptFlag1 = false;
    Serial.println("X Threshold Reached!");

    int xThresh = sensor1.getXThreshold();
    Serial.print("Sensor 1's X Threshold: ");
    Serial.println(xThresh);

    if (sensor1.getMagneticChannel() != 0)  // Checks if mag channels are on - turns on in setup
    {
      float magX = sensor1.getXData();
      float magY = sensor1.getYData();
      float magZ = sensor1.getZData();
      float temp = sensor1.getTemp();

      Serial.print("(");
      Serial.print(magX);
      Serial.print(", ");
      Serial.print(magY);
      Serial.print(", ");
      Serial.print(magZ);
      Serial.println(") mT");
      Serial.print(temp);
      Serial.println(" °C");
    } 
    else 
    {
      Serial.println("Mag Channels disabled, stopping..");
      while (1);
    }
  }

  if (interruptFlag2 == true) 
  {
    interruptFlag2 = false;
    Serial.println("X Threshold Reached!");

    int xThresh = sensor2.getXThreshold();
    Serial.print("Sensor 2's X Threshold: ");
    Serial.println(xThresh);

    if (sensor2.getMagneticChannel() != 0)  // Checks if mag channels are on - turns on in setup
    {
      float magX = sensor2.getXData();
      float magY = sensor2.getYData();
      float magZ = sensor2.getZData();
      float temp = sensor2.getTemp();

      Serial.print("(");
      Serial.print(magX);
      Serial.print(", ");
      Serial.print(magY);
      Serial.print(", ");
      Serial.print(magZ);
      Serial.println(") mT");
      Serial.print(temp);
      Serial.println(" °C");
    } 
  else
  {
    Serial.println("Checking for Interrupts...");
  }
  }

  // Small delay to avoid flooding the serial monitor
  delay(500);
}