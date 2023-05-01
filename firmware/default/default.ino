
String password = "admin123";
String message = "S3rial_P1n_4tt4ck";
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
