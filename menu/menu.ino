int choice;
////////////////////////i2c Master and slave
#include <Wire.h>// Include Arduino Wire library for I2C
#define SLAVE_ADDR 9// Define Slave I2C Address
#define ANSWERSIZE 5// Define Slave answer size
#define HIGH_FREQ 1000 // define high frequency
#define LOW_FREQ 500 // define low frequency
////////////////////////i2cSlave
// Define string with response to Master
String answer = "N0St4ck_Buff3rs";
////////////////////////spiMaster and Slave
#include <SPI.h>
////////////////////////
String password = "admin123";
String message = "S3rial_P1n_4tt4ck";
String currentPassword = "";
bool finished = false;
String rx = "";
bool first = true;
//////////////////////////
void setup() {
  Serial.begin(9600);   // initialize serial communication at 9600 bits per second
  Serial.print("\nEnter your choice :\n  1. Signal Analysis \n  2. UART\n");
  pinMode(9, OUTPUT); // set digital pin 9 as output

  while(Serial.available()<=0){
    //donothing
    delay(1);
  }
  delay(100);
  choice = Serial.parseInt();
  Serial.println(choice);
  switch (choice) {
    case 1://custom signal
      Wire.begin();
      Serial.print("Selected ");
      Serial.print(choice);
      Serial.print(" : Signal Analysis");
      break;

    case 2://Uart
      Serial.print("Selected ");
      Serial.print(choice);
      Serial.print(" : UART");
      break;
  }

}

/////////////////////////////////////////////////////////////
void receiveEvent() {
  while (0 < Wire.available()) {// Read while data received
    byte x = Wire.read();
  }
  Serial.println("Receive event"); // Print to Serial Monitor
}

void requestEvent() {
  byte response[ANSWERSIZE];// Setup byte variable in the correct size
  for (byte i=0;i<ANSWERSIZE;i++) {// Format answer as array
    response[i] = (byte)answer.charAt(i);
  }
  Wire.write(response,sizeof(response)); // Send response back to Master
  Serial.println("Request event");// Print to Serial Monitor
}


/////////////////////////////////////////////////////////////////////////////////
void uartDefault(){
  Serial.println("UART Challenge loading...");
      Serial.begin(9600);
      while (!Serial) {
         // wait for serial port to connect. Needed for native USB port only
      }
      currentPassword = "";
      String m = message;
      Serial.println("I have confidential message. Pass ?");
      while(!finished) {
        if (currentPassword != password) {
          if (!first) {
            Serial.println("Wrong password");
            Serial.println("Try again");
            delay(50);
            currentPassword = "";
          }
          if (Serial.available() > 0) {
            rx = Serial.readString();
            currentPassword = currentPassword + rx;
            currentPassword.trim();
            Serial.println("Pass : " + currentPassword);
            delay(50);
            first = false;
            delay(2000);
          }
        }
        else{
          Serial.print("Well done! Message: ");
          Serial.print(m);
          Serial.print(" ");
          finished = true;
          exit;
        }
      }
}
/////////////////////////////////////////////////////////////////////////////////
void custompro(){
    String message = "FSK"; // the message to transmit
  String binary = ""; // binary representation of the message

  // convert message to binary
  for (int i = 0; i < message.length(); i++) {
    // convert character to binary and add leading zeros if necessary
    String binary_char = String(message[i], BIN);
    while (binary_char.length() < 8) {
      binary_char = "0" + binary_char;
    }
    binary += binary_char + ' ';
  }

  // modulate the signal
  for (int i = 0; i < binary.length(); i++) {
    if (binary[i] == '0') {
      tone(9, LOW_FREQ); // transmit low frequency
    } else if (binary[i] == '1')  {
      tone(9, HIGH_FREQ); // transmit high frequency
    }
    else{
      noTone(9);
    }
    delay(100); // delay for 100 ms
    noTone(9); // stop transmitting
  }
}
/////////////////////////////////////////////////////////////////////////////////

void loop() {
  digitalWrite(LED_BUILTIN, HIGH);  // turn the LED on (HIGH is the voltage level)
  delay(100);                      // wait for a second
  digitalWrite(LED_BUILTIN, LOW);   // turn the LED off by making the voltage LOW
  delay(100); 

  switch (choice) {
    case 1:
      custompro();
      break;
    case 2:
      uartDefault();
      break;
  }
  
}
