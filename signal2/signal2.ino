#define HIGH_FREQ 1000 // define high frequency
#define LOW_FREQ 500 // define low frequency
#define BAUD_RATE 9600 // define baud rate

void setup() {
  Serial.begin(BAUD_RATE); // initialize serial communication
  pinMode(9, OUTPUT); // set digital pin 9 as output
}

void loop() {
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
  Serial.println(binary);

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
