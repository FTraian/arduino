#include <SparkFunColorLCDShield.h>
#include <DHT.h>
#include <DHT_U.h>

#define BACKGROUND  BLACK  // room for growth, adjust the background color according to daylight

LCDShield lcd;

int buttonPins[3] = {3, 4, 5};

#define DHTPIN 7
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);

#define FILTER_DEPTH 256
static float sum;

unsigned long timeStart = 0;

void setup()
{
  /* Set up the button pins as inputs, set pull-up resistor */
  for (int i = 0; i < 3; i++)
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

  timeStart = millis();
}

void loop()
{
  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  float h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();

  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t)) {
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

  drawData(0, t, h, hic);
  drawData(1, filter(t), h, hic);

  delay(100);
}

float filter(float sample) {
  sum -= sum / FILTER_DEPTH;
  sum += sample;

  return sum / FILTER_DEPTH;
}

void drawData(int row, float temp, float hum, float tempIdx) {
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

  lcd.setStr(lcdStr, row * 13, 4, WHITE, BACKGROUND);
}
