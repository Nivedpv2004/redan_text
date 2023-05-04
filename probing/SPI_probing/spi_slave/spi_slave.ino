#include <SPI.h>
int SS = 10;

void setup() {
  Serial.begin(9600); // initialize serial communication for debugging
  SPI.begin(); // initialize SPI communication
  pinMode(SS, INPUT_PULLUP); // set SS pin as input with pullup
}

void loop() {
  if (digitalRead(SS) == LOW) { // if the slave is selected
    int length = SPI.transfer(0); // receive the length of the message
    String message = "";
    for (int i = 0; i < length; i++) {
      message += (char)SPI.transfer(0); // receive each character of the message
    }
    Serial.println(message); // print the received message
    while (digitalRead(SS) == LOW); // wait until the slave is deselected
  }
}
