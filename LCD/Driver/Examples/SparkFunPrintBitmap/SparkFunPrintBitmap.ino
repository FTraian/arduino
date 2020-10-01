/*
  PrintBitmap - An example sketch for the SparkFun Color LCD Shield Library
  by: Jim Lindblom
  SparkFun Electronics
  date: 6/23/11
  license: CC-BY SA 3.0 - Creative commons share-alike 3.0
  use this code however you'd like, just keep this license and
  attribute. Let me know if you make hugely, awesome, great changes.
  
  This sketch allows for printing of monochrome bitmap images on the display. They must be no
  larger than 128 by 128 pixels, and must be written in the char hexadecimal format used with C. 
  A good convertor for windows can be found at http://en.radzio.dxp.pl/bitmap_converter/ . It
  should be converted in horizontal order.
  
  Bitmap printing additions made by Jacob Unwin (http://www.jacob-unwin.com )
  */
  
  #include <SparkFunColorLCDShield.h>
  
  LCDShield lcd;
  
  //this is the correct number of bytes for a 128 by 128 image. (I used the sparkfun logo) The image must be encoded horizontally
  //for it to display correctly
  char myBitmap[2048] = {
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x78,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xf0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0xe0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0xe0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0xf0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xfb,0x80,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0x80,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x7f,0x80,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x0c,0x3f,0xc0,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x1c,0x3f,0xc0,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x3c,0x7f,0xc0,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x3f,0xff,0x80,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x3f,0xff,0x80,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x3f,0xff,0x80,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x3f,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x3f,0xfe,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x3f,0xfc,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x3f,0xe0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x3e,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x3c,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x38,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x30,0x0f,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x0e,0x20,0x1f,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x1e,0x00,0x3f,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x1e,0x00,0x3c,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x1e,0x00,0x3c,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x0f,0xe0,0x9f,0x01,0xfc,0x09,0x9e,0x1e,0x7f,0x70,0x73,0x9f,0x00,0x00,0x00,0x00,
0x3f,0xf1,0xff,0x87,0xfe,0x3f,0xde,0x3d,0xff,0x78,0xf3,0xff,0x80,0x00,0x00,0x00,
0x3c,0xf9,0xff,0xc7,0xdf,0x3f,0xde,0x79,0xff,0x78,0xf3,0xff,0xc0,0x00,0x00,0x00,
0x78,0x79,0xc3,0xcf,0x0f,0x3f,0x1c,0xf0,0x3c,0x78,0xf3,0xe3,0xc0,0x00,0x00,0x00,
0x7c,0x01,0xc1,0xe0,0x0f,0x3e,0x1f,0xe0,0x3c,0x78,0xf3,0xc3,0xc0,0x00,0x00,0x00,
0x3f,0xc1,0x81,0xe0,0x3f,0x3c,0x1f,0xe0,0x3c,0x78,0xf3,0xc1,0xc0,0x00,0x00,0x00,
0x1f,0xf1,0x81,0xe3,0xff,0x3c,0x1f,0xe0,0x3c,0x78,0xf3,0xc1,0xc0,0x00,0x00,0x00,
0x07,0xf9,0x81,0xe7,0xef,0x3c,0x1f,0xf0,0x3c,0x78,0xf3,0xc1,0xc0,0x00,0x00,0x00,
0x00,0xf9,0x81,0xef,0x07,0x3c,0x1e,0xf8,0x3c,0x78,0xf3,0xc1,0xc0,0x00,0x00,0x00,
0x78,0x79,0xc1,0xef,0x0f,0x3c,0x1e,0x78,0x3c,0x78,0xf3,0xc1,0xc0,0x00,0x00,0x00,
0x78,0x79,0xe3,0xcf,0x0f,0x3c,0x1e,0x3c,0x3c,0x7c,0xf3,0xc1,0xc0,0x00,0x00,0x00,
0x3f,0xf9,0xff,0xcf,0xff,0x3c,0x1e,0x3e,0x3c,0x7f,0xf3,0xc1,0xcf,0x00,0x00,0x00,
0x1f,0xf1,0xff,0x87,0xff,0x3c,0x1e,0x1e,0x3c,0x3f,0xf3,0xc1,0xc7,0x00,0x00,0x00,
0x07,0xc1,0x9e,0x03,0xe0,0x00,0x00,0x02,0x00,0x0e,0x20,0x00,0x00,0x00,0x00,0x00,
0x00,0x01,0x80,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x01,0x80,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x03,0x80,0x00,0x00,0x00,0xc0,0x00,0x00,0x18,0x00,0x00,0x08,0x08,0x00,0x00,
0x00,0x01,0x87,0xc3,0x03,0xe0,0xe1,0xf0,0xf8,0x3e,0x33,0x08,0x3e,0x1e,0x00,0x00,
0x00,0x01,0x86,0x03,0x03,0x01,0xb0,0xe0,0xdc,0x66,0x3b,0x08,0x66,0x32,0x00,0x00,
0x00,0x00,0x87,0xc3,0x03,0xe1,0x80,0x40,0xd8,0x63,0x3b,0x08,0x60,0x3c,0x00,0x00,
0x00,0x00,0x87,0x83,0x03,0xc1,0x80,0x40,0xf8,0x63,0x3f,0x08,0x60,0x0e,0x00,0x00,
0x00,0x00,0x06,0x03,0x03,0x01,0xb0,0x40,0xd8,0x66,0x37,0x08,0x66,0x32,0x00,0x00,
0x00,0x00,0x07,0xc3,0xe3,0xe0,0xe0,0x40,0xc8,0x3e,0x33,0x08,0x3e,0x3e,0x00,0x00,
0x00,0x00,0x07,0xc3,0xe3,0xe0,0xe0,0x40,0x88,0x3c,0x33,0x08,0x3c,0x1e,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
  }; 
    
    void setup(){
       // Initialize the LCD, try using EPSON if it's not working
  lcd.init(PHILIPS);  
  // lcd.init(PHILIPS, 1);  // Philips init with colors swapped. (Try this if red makes blue, etc).
  lcd.contrast(-51);  // Initialize contrast
  lcd.clear(WHITE);  // Set background to white
  lcd.printBMP(myBitmap); //prints the bitmap
    }
    
    void loop(){
      //we don't need to loop anything
    };