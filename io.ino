#include <Wire.h>


#define MCP4725_ADDR 0x60


// Function to set voltage on MCP4725
void setVoltage(int voltage) {
 Wire.beginTransmission(MCP4725_ADDR);
 Wire.write(64); // Control byte to update the DAC
 Wire.write((voltage >> 4) & 0xFF); // Upper data bits
 Wire.write((voltage & 0x0F) << 4); // Lower data bits
 Wire.endTransmission();
}


void setup() {
 Serial.begin(9600);
 Wire.begin();
 pinMode(A0, INPUT);
 randomSeed(analogRead(0)); // Initialize random number generator
}


void loop() {
 int randomValue = random(0, 4096); // Generate a random value for the DAC
 setVoltage(randomValue); // Set DAC voltage
 delayMicroseconds(1000); // Wait 1 millisecond
  int expectedVoltage = map(randomValue, 0, 4095, 0, 5000); // Expected mV (assuming 5V reference)
 int sensorValue = analogRead(A0);
 float measuredVoltage = sensorValue * (5000.0 / 1023.0); // Measured mV
  // Calculate error in millivolts
 float error = expectedVoltage - measuredVoltage;
  // Print error
 Serial.print("Expected: ");
 Serial.print(expectedVoltage);
 Serial.print(" mV, Measured: ");
 Serial.print(measuredVoltage);
 Serial.print(" mV, Error: ");
 Serial.print(error);
 Serial.println(" mV");
  delayMicroseconds(1000 - (micros() % 1000)); // Adjust timing if needed
}

