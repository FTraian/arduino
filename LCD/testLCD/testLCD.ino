// Color LCD Shield library
#include "Nokia_LCD_driver.h"

LCDShield lcd;  // Creates an LCDShield, named lcd

void setup()
{
  lcd.init(PHILIPS);  // Initializes lcd, using an PHILIPS driver
  lcd.contrast(-51);  // 40's usually a good contrast value
  lcd.clear(TEAL);  // oooh, teal!
}

void loop()
{
}
