#include <SPI.h>

void setup() {
  Serial.begin(9600); // initialize serial communication for debugging
  SPI.begin(); // initialize SPI communication
  pinMode(SS, OUTPUT); // set SS pin as output
  digitalWrite(SS, HIGH); // set SS pin high initially
}

void loop() {
  String message = "D1g1t4l_F0rens1cs"; // create the message to send
  digitalWrite(SS, LOW); // select the slave
  SPI.transfer(message.length()); // send the length of the message
  for (int i = 0; i < message.length(); i++) {
    SPI.transfer(message[i]); // send each character of the message
  }
  digitalWrite(SS, HIGH); // deselect the slave
  delay(1000); // wait for a second before sending the next message
}
