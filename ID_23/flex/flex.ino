#include <SPI.h>
#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_ST7735.h> // Hardware-specific library
#include <Wire.h>            // Wire library for I2C communication(for ADXL345) 
#include <Adafruit_ST7789.h>

#if defined(ARDUINO_FEATHER_ESP32) // Feather Huzzah32
  #define TFT_CS         14
  #define TFT_RST        15
  #define TFT_DC         32

#elif defined(ESP8266)
  #define TFT_CS         4
  #define TFT_RST        16                                            
  #define TFT_DC         5

#else
  // For the breakout board, you can use any 2 or 3 pins.
  // These pins will also work for the 1.8" TFT shield.
  #define TFT_CS        10
  #define TFT_RST        12 // Or set to -1 and connect to Arduino RESET pin
  #define TFT_DC         9
#endif

int ADXL345 = 0x53 ; // ADXL345 sensor i2c address
int X_out, Y_out, Z_out;// output of x y z orientation of ADXL345

int o=0,p=0,k=0;
int time=0;


Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_RST);
void setup(void) {
  tft.initR(INITR_144GREENTAB); // Init ST7735R chip, green tab
  
  tft.setRotation(0); // set display orientation 


  
/////////////////////////////////////////////////////////////////////////////


  tft.fillScreen(ST77XX_BLUE);
  tft.fillRect(0, 100, 150, 60,  ST77XX_GREEN);
  tft.fillCircle(102, 20, 12, ST77XX_YELLOW);
  print_text(20,40,"FLEX",3,ST77XX_ORANGE);

  tft.fillCircle(100, 75, 10, ST7735_GREEN);

  tft.fillRect(100, 80, 4, 20, ST7735_RED);

 // first screen//////////////////////////////////// 
  
tft.fillCircle(50, 90, 7, ST7735_RED);

delay(1000);
tft.fillScreen(ST77XX_BLUE);

Serial.begin(9600); //initiate serial coommunication
Wire.begin(); //initiate wire library
Wire.beginTransmission(ADXL345); //transmission begin
Wire.write(0x2D); // Access toPOWER_CTL Register -0x2D
Wire.write(8); // Bit D3 High for measuring enable (8dec -> 0000 1000 binary)
Wire.endTransmission();

}


////////////////////////////////////////////
 

void object(int c,int tim){
  if(256-2*c>=13&&256-2*c<=27&&113-o>=84){    // 
  // tft.setTextWrap(false);
  tft.fillScreen(ST77XX_YELLOW);
  tft.setCursor(15, 30);
  tft.setTextColor(ST77XX_BLACK);
  tft.setTextSize(2);
  tft.println("GAME OVER");
  tft.setCursor(40, 55);
  tft.setTextColor(ST77XX_RED);
  tft.setTextSize(2);
  tft.println("SCORE:");
  tft.setCursor(45, 80);
  tft.setTextSize(3);
  tft.setTextColor(ST77XX_RED);
  tft.print(time, 6);
 object(c,tim);
  }
  tft.fillCircle(40, 20, 12, ST77XX_WHITE);
   tft.fillCircle(23, 22, 9, ST77XX_WHITE);
    tft.fillCircle(59, 22, 9, ST77XX_WHITE);
 tft.fillCircle(102, 20, 12, ST77XX_YELLOW);

 
 tft.fillRect(0, 122, 128, 6,  ST77XX_GREEN);//ground
 
 Wire.beginTransmission(ADXL345);
  Wire.write(0x32);
  Wire.endTransmission(false);
  Wire.requestFrom(ADXL345, 6, true);

  X_out = ( Wire.read() | Wire.read() << 8); 
  Y_out = ( Wire.read() | Wire.read() << 8);
  Z_out = ( Wire.read() | Wire.read() << 8);

  Serial.print(X_out);
  Serial.print(" ");
  Serial.print(Y_out);
  Serial.print(" ");
  Serial.println(Z_out);


if (Y_out>40||o>0){
if(o<47){
 tft.fillCircle(25, 113-o, 7, ST7735_RED);//ball jump
 o++;
}
if(o>=47){
  tft.fillCircle(25, 113-o+p, 7, ST7735_RED);//ball jump
  p++;
  if(113-o+p==113){
    o=0;
    p=0;
    }
    }
}
else{
   tft.fillCircle(25, 113-o, 7, ST7735_RED);
}

tft.fillCircle(256-2*c, 102, 9, ST7735_GREEN);//tree
  tft.fillRect(256-2*c, 105, 4, 20, ST7735_RED);//tree

  
c=c+1;
tim=tim+1;
  delay(15);

  //if(c!=145){

  

  if (Y_out>45||o>0){
  if(o<47){
 tft.fillCircle(25, 113-o+1, 7, ST7735_BLUE);//ball jump
 o++;
}
if(o>=47){
  tft.fillCircle(25, 113-o+p-1, 7, ST7735_BLUE);//ball jump
  p++;
  if(113-o+p==113){
    o=0;
    p=0;
    }
    }
  }
  
  
  
  
   tft.fillCircle(256-2*c+2*1, 102, 9, ST7735_BLUE);//tree
   
  tft.fillRect(256-2*c+2*1, 105, 4, 20, ST7735_BLUE);//tree
  
  
if(tim<=65){
  
object(c,tim);

}




}
/////////////////////////////////////////////////////////  

void loop(){
time=time+10;  
 int tim=0;
 int c=64;
object(c,tim);



 


}

void print_text(byte x_pos, byte y_pos, char *text, byte text_size, uint16_t color)
{
  tft.setCursor(x_pos, y_pos);
  tft.setTextSize(text_size);
  tft.setTextColor(color);
  tft.setTextWrap(true);
  tft.print(text);
}
