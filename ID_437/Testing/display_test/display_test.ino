#include <SPI.h>
#include <Adafruit_GFX.h>
#include <TFT_ILI9163C.h>
// #include <Wire.h>
// #include<string.h>
// #include<stdlib.h>

#define BLACK   0x0000
#define BLUE    0x001F
#define RED     0xF800
#define GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0  
#define WHITE   0xFFFF
#define BROWN   0xFB00
#define DARKBROWN 0x8041

TFT_ILI9163C display = TFT_ILI9163C(10, 8, 9);

void setup() {
  // put your setup code here, to run once:
  display.begin();
  display.setTextSize(2);
  display.setCursor( 5 , 40 );
  display.println("   Hii");

  //display corners
  display.drawPixel(2, 1, WHITE);
  display.drawPixel(128, 1, WHITE);
  display.drawPixel(2, 127, WHITE);
  display.drawPixel(128, 127, WHITE);

}

void loop() {
  // put your main code here, to run repeatedly:

}
