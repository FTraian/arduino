#include <SoftwareSerial.h>
SoftwareSerial mySerial(4, 3); // RX, TX


void setup() {
  Serial.begin(9600);
  while(!Serial);
  
  mySerial.begin(9600);
  delay(2000);
  
  Serial.println("Setup done!");
}

void loop() {
  if (Serial.available()) {      // If anything comes in Serial (USB),
    char input = Serial.read();
    Serial.write(input);
    mySerial.write(input);   // read it and send it out to SIM module
  }

  if (mySerial.available()) {     // If anything comes from SIM module
    Serial.write(mySerial.read());   // read it and send it out Serial (USB)
  }
}
