
// Include Arduino Wire library for I2C
#include <Wire.h>

// Define Slave I2C Address
#define SLAVE_ADDR 9

// Define Slave answer size
#define ANSWERSIZE 5

void setup() {

  // Initialize I2C communications as Master
  Wire.begin();
  
  // Setup serial monitor
  Serial.begin(9600);
}

void loop() {
 
  
  // Write a charatre to the Slave
  Wire.beginTransmission(SLAVE_ADDR);
  Wire.write(0);
  Wire.endTransmission();
    
  
  // Read response from Slave
  // Read back 5 characters
  Wire.requestFrom(SLAVE_ADDR,ANSWERSIZE);
  
  // Add characters to string
  String response = "";
  while (Wire.available()) {
      char b = Wire.read();
      response += b;
  } 
  
  // Print to Serial Monitor
  Serial.println(response);
}