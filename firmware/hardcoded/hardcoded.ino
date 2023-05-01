
String password = "embeddedisfun";
String message = "B00111n478r0y_M412s0k";
String currentPassword = "";
bool finished = false;
String rx = "";
bool first = true;



void setup()
{
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  currentPassword = "";

 

  String m = String(message[0])+String(message[3])+String(message[6])+String(message[7])+String(message[10])+String(message[12])+String(message[13])+String(message[14])+String(message[15])+String(message[18])+String(message[20]);
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
    else
    {
     Serial.print("Well done! Message: ");
Serial.print(m);
Serial.print(" ");

      finished = true;
    }


  }

}

void loop() {}
