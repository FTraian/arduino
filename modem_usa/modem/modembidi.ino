#include <SoftwareSerial.h>
SoftwareSerial mySerial(4, 3); // TX, RX


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
    mySerial.write(input);   // read it and send it out Serial1 (pins 0 & 1)
  }

  if (mySerial.available()) {     // If anything comes in Serial1 (pins 0 & 1)
    Serial.write(mySerial.read());   // read it and send it out Serial (USB)
  }
}
