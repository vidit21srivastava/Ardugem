#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>
#include<Wire.h>
#include "marioblack.h"




#define __CS 10
#define __DC 9
#define __RST 12
Adafruit_ST7735 tft = Adafruit_ST7735(__CS, __DC,__RST);
// Color definitions
#define	BLACK   0x0000
#define	RED     0x001F
#define	BLUE    0xF800
#define	GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0  
#define WHITE   0xFFFF
//const int buttonPin = 7;
//int buttonState = 0;

const int charwi = 10;
const int charhi = 10;
const int platwi = 240;
const int plathi = 40;
const int platY = 110;
const int minobs = 30;
const int maxobs = 40;
const int obswi= 10;
const int obspace = 100;
const int obscount = 3;
const int obspeed = 3;
const int humphi = 100;
int charX = 20;
int charY = 70;
int charYSpeed = 0;
int platX = 0;
int platSpeed = 4;
int obstacleX[obscount];
int obstacleY[obscount];
int ADXL345 = 0X53;
int y_out;
int x_out;
int z_out;


#define TFTW            128     // screen width
#define TFTH            160     // screen height
#define TFTW2            64     // half screen width
#define TFTH2            80     // half screen height
int check=0;
int num=0;
int score=0;

void setup()
{
    tft.initR(INITR_BLACKTAB);
    
     
tft.fillScreen(BLACK);
    tft.setRotation(3);
  tft.fillRect(10, TFTH2 - 20, TFTW-20, 1, WHITE);
  tft.fillRect(10, TFTH2 + 32, TFTW-20, 1, WHITE);
  tft.setTextColor(WHITE);
  tft.setTextSize(3);
  // half width - num char * char width in pixels
  tft.setCursor( TFTW2-(6*9), TFTH2 - 16);
  tft.println("BTECH");
  tft.setTextSize(3);
  tft.setCursor( TFTW2-(6*9), TFTH2 + 8);
  tft.println("-SAGA-");
  tft.setTextSize(0);
  tft.setCursor( 10, TFTH2 - 28);
  tft.setCursor( TFTW2 - (12*3) - 1, TFTH2 + 34);
  tft.println("Let's Go!!!");
  delay(2000);
  tft.fillScreen(BLACK);
  tft.setCursor(25, 60);
  tft.setTextColor(WHITE);
  tft.setTextSize(2);
 

  tft.print("Loading");
  delay(500);
  float i;
  for( i= 0; i<82; i=i+0.5){
  tft.fillRect(25,80,i,5,WHITE);
}
delay(1000);
    
  tft.fillScreen(BLACK);
    tft.setRotation(3);
    

    for (int i = 0; i < obscount; i++)
    {
        obstacleX[i] = platwi + i * obspace;
        obstacleY[i] = platY - random(minobs, maxobs);
    }
Serial.begin(9600);
Wire.begin();
Wire.beginTransmission(ADXL345);
Wire.write(0X2D);
Wire.write(8);
Wire.endTransmission();
delay(1000);
  

    
}

void loop()
{

score=score+1;

Wire.beginTransmission(ADXL345);
Wire.write(0X32);
Wire.endTransmission(false);
Wire.requestFrom(ADXL345,6,true);
x_out = (Wire.read()|Wire.read()<<8);
y_out = (Wire.read()|Wire.read()<<8);
z_out = (Wire.read()|Wire.read()<<8);


//y_out = (Wire.read()|Wire.read()<<8);
tft.fillRect(0,0,128,60,BLACK);
Serial.println(z_out);
    //tft.fillRect(charX, charY, charwi, charhi,BLACK);
    for (int i = 0; i < obscount; i++)
    {
        tft.fillRect(obstacleX[i], obstacleY[i], obswi, platY - obstacleY[i],BLACK);
      
    }

    platX += platSpeed;
    if (platX < 0 || platX + platwi > tft.width())
    {
        platSpeed = -platSpeed;
    }

    for (int i = 0; i < obscount; i++)
    {
        obstacleX[i] = obstacleX[i] - obspeed;
        if (obstacleX[i] + obswi< 0)
        {
                  
                            obstacleX[i] = tft.width() + obspace;
            obstacleY[i] = platY - random(minobs, maxobs);
        }
    }

    
    if ((z_out>3) )
    {
     charYSpeed = -2;
    
    charY += charYSpeed;
    charYSpeed++;
    
//charY=charY-(y_out/100);
    }
    
    

  

    if (charY<10)
    {
      for(int i=1;i<65;i++){
        charY=charY+1;
        
              
        charYSpeed = 0;
      }
    }
    if (charY > platY)
    {
        charY = platY - 20;
        charYSpeed = 0;
    }
    tft.fillRect(platX,105,platwi,5,GREEN);
    tft.fillRect(platX, platY, platwi, plathi,RED);

    

    
    tft.drawBitmap(charX,charY,mario,19,30,WHITE);
tft.drawBitmap(charX,charY,mario,19,30,WHITE);    
    //delay(50);
    tft.drawBitmap(charX,charY,mario,19,30,BLACK);

    for (int i = 0; i < obscount; i++)
    {
        tft.fillRect(obstacleX[i], obstacleY[i], obswi, platY - obstacleY[i],CYAN);
      
             
        
        if(check==1){
          tft.println("SCORE:");
          tft.print(score);
                    
            while(1){
            
          }
        }        
        
          

       }
       int i;
if((obstacleX[i]==charX+15)||(obstacleY[i]==charY)){
        check=1;
               
        tft.fillScreen(BLACK);
        tft.setTextColor(WHITE);
        tft.setTextSize(2);
        
        //tft.setCursor( TFTW2 - (9*6), TFTH2-20 );
        tft.setCursor(20,20);
        tft.println("GAME OVER!");
        delay(4000);        
        tft.fillScreen(BLACK);
        
          
                  }       
        
        
        }
    
   
    
    
        
        

    
