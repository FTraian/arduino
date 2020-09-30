int ledPin = 3;

void setup() {
  Serial.begin(9600);
  Serial.println("Serial connection started, waiting for instructions…n0 = Offn1 = 25%n2 =50%n3 = 75%n4 = 100%");
}

void loop () {
  if (Serial.available()) {
    char ser = Serial.read(); //read serial as a character
    
    //NOTE because the serial is read as “char” and not “int”, the read value must be compared to character numbers
    //hence the quotes around the numbers in the case statement
    
    switch (ser)
    {
      case '0':
        analogWrite(ledPin, 0);
        Serial.println("Received 0");
        break;
      
      case '1':
        analogWrite(ledPin, 64);
        Serial.println("Received 1");
        break;
      
      case '2':
        analogWrite(ledPin, 128);
        Serial.println("Received 2");
        break;
      
      case '3':
        analogWrite(ledPin, 192);
        Serial.println("Received 3");
        break;
      
      case '4':
        analogWrite(ledPin, 255);
        Serial.println("Received 4");
        break;
      //default:
        //Serial.println("Invalid entry");
      
    }
  }
}
