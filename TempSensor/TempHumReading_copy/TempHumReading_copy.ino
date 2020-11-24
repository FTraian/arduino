#include <SparkFunColorLCDShield.h>
#include <DHT.h>
#include <DHT_U.h>

#define BACKGROUND  BLACK  // room for growth, adjust the background color according to daylight

LCDShield lcd;

int buttonPins[3] = {3, 4, 5};

#define DHTPIN 7
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);

void setup()
{
  /* Set up the button pins as inputs, set pull-up resistor */
  for (int i=0; i<3; i++)
  {
    pinMode(buttonPins[i], INPUT);
    digitalWrite(buttonPins[i], HIGH);
  }
  
  /* Initialize the LCD, set the contrast, clear the screen */
  lcd.init(EPSON);
  lcd.contrast(40);
  lcd.clear(BACKGROUND);
  
  Serial.begin(9600);
  Serial.println(F("DHTxx test!"));
  dht.begin();
}

void loop()
{
  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  float h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();
  // Read temperature as Fahrenheit (isFahrenheit = true)
  float f = dht.readTemperature(true);

  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }

  // Compute heat index in Celsius (isFahreheit = false)
  float hic = dht.computeHeatIndex(t, h, false);

  Serial.print(F("Humidity: "));
  Serial.print(h);
  Serial.print(F("%  Temperature: "));
  Serial.print(t);
  Serial.print(F("°C "));
  Serial.print(F(" Heat index: "));
  Serial.print(hic);
  Serial.print(F("°C\n"));
  
  drawData(t, h, hic);
}

void drawData(float temp, float hum, float tempIdx) {
  char lcdStr[20];
  char str[5];
  
  dtostrf(temp, 4, 1, str);
  strcpy(lcdStr, str);
  strcat(lcdStr, "C ");
  
  dtostrf(hum, 2, 0, str);
  strcat(lcdStr, str);
  strcat(lcdStr, "% ");
  
  dtostrf(tempIdx, 4, 1, str);
  strcat(lcdStr, str);
  strcat(lcdStr, "R");
  
  lcd.setStr(lcdStr, 0, 4, WHITE, BACKGROUND);
}