#include <math.h>
#include <TFT_ILI9163C.h>
#include <Adafruit_Sensor.h> 
#include <Adafruit_ADXL345_U.h>
#include "logo.h"
Adafruit_ADXL345_Unified accel = Adafruit_ADXL345_Unified();


short buttonState = LOW;
const short BALL_UPDATE_MS = 20;
const short GAME_UPDATE_MS = 500;
const unsigned short BUTTON_PIN = 7;

const short ROWS = 128;
const short COLUMNS = 16;


float AccelX = 0;
float AccelY = 0;
float AccelZ = 0;
float X = 0;
float Y = 0;
float Z = 0;
int cal_var = 0;

#define cs 10
#define dc 8
#define rst 9

#define BLACK   0x0000
#define BLUE    0x001F
#define RED     0xF800
#define GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0  
#define WHITE   0xFFFF

TFT_ILI9163C display = TFT_ILI9163C(cs,dc,9);

int nextUpdate = 0;
int nextBallUpdate = 0;
int score = 0;
unsigned int inAirStart = 0;
const short USER_POSITION = 8192;
unsigned short currentObstacles = 1;
uint8_t obstacleBlock[8] = {
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00100,
  B01110,
  B11111,
};
uint8_t ballBlock[8] = {
  B00000,
  B00000,
  B00000,
  B01110,
  B11111,
  B11111,
  B11111,
  B01110,
};
uint8_t deflatedBallBlock[8] = {
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B01110,
  B11111,
  B11111,
};

uint8_t BlankBall[8] = {
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
};

unsigned short generateObstacles();
void paintObstacles();
bool isInAir();
bool hasLost();
void paintBall();
void gameOver();

unsigned short generateObstacles() {
  long randNumber = random(0, 9);
  unsigned short newNumber = currentObstacles << 1;

  if (randNumber < 3) {
    newNumber = newNumber | 0x1;
  }

  return newNumber;
}

void paintObstacles() {
  display.clearScreen();
  unsigned short printObstacles = currentObstacles;
//  Serial.println(printObstacles);
  for (short i = 120; i >= 1; i-=8) {
    bool hasObstacle = printObstacles & 0x1;
    score++;
//    Serial.println(printObstacles);
    if(hasObstacle)
    {
      display.drawBitmap(i,40,obstacleBlock,8,10,YELLOW);
    }
    printObstacles = (printObstacles >> 1);
  }
}

bool isInAir() {
  return inAirStart > 0 && (millis() - inAirStart) < (GAME_UPDATE_MS * 10);
}

bool hasLost() {
  return (USER_POSITION & currentObstacles) != 0 && !isInAir();
}

void paintBall() {
  short columnPosition = COLUMNS - (log10(USER_POSITION) / log10(2));
  for(short j=0;j<8;j++)
  {
    for( short k=40;k<50;k++)
    {
      display.setCursor(1<<(columnPosition - 1) +1, k);
      display.print(' ');
    }
  }
  

  if ((USER_POSITION & currentObstacles) == 0) {
    for(short j=0;j<8;j++)
    {
      for( short k=40;k<50;k++)
      {
        display.setCursor(1<<(columnPosition - 1) +1, k+10);
        display.print(' ');
      }
    }
  }
  if(hasLost())
    display.drawBitmap(1<<(columnPosition - 1) +1, 30+10*(!isInAir()),deflatedBallBlock,8,10,GREEN);
  else
    display.drawBitmap(1<<(columnPosition - 1) +1, 30+10*(!isInAir()),ballBlock,8,10,GREEN);
  delay(500);
}

void gameOver(sensors_event_t &event, float AccelX) {

   
  float X1 = event.acceleration.x - AccelX;
  display.clearScreen();
  display.setCursor(40,20);
  display.setTextSize(1.35);
  display.print("GAME OVER");
  display.setCursor(10,80);
  display.print("SCORE: ");
  display.print(score-195);
  display.setCursor(35,40);
  display.print("Play Again");
  for(;;)
  {
    if(X1>3)
    break;
  }
  return;
}

void setup() {
 
  display.begin();
  Serial.begin(19200);
  accel.begin();
  //accel.setDataRate(100);
   sensors_event_t event; 
  accel.getEvent(&event);
  callibrate(event);
  
  X = event.acceleration.x - AccelX; 
  Y = event.acceleration.y - AccelY; 
  Z = event.acceleration.z - AccelZ;
  Intro();
  display.clearScreen();
}



void Intro(){
  display.clearScreen();
  display.setRotation(0);         // Rotate to portrait
  display.fillScreen(BLACK); // Clear screen if necessary
  display.setTextColor(GREEN,BLACK);
  display.setTextSize(1);
  display.setCursor(60,25);
  display.println("BOUNCY BALL");
  delay(500);
  int logo_origin_x = (80 - 2*LOGO_WIDTH ) / 2;
  int logo_origin_y = (100 - 2*LOGO_HEIGHT) / 2;
  for(int y=0; y<LOGO_HEIGHT; y++) {
    for(int x=0; x<LOGO_WIDTH; x++) {
      uint8_t c = logo_mask[y][x / 8];
      if(c & (0x80 >> (x & 7))) {
        int xx = logo_origin_x+2*x;
        int yy = logo_origin_y+2*y;
        display.drawPixel(xx, yy, CYAN);
        display.drawPixel(xx+1, yy, CYAN);
        display.drawPixel(xx, yy+1, CYAN);
        display.drawPixel(xx+1, yy+1, CYAN);
      }
    }
  }
  delay(500);
  for (int i=0; i<10; i++) {
    delay(50);
  }

 display.clearScreen();
 display.setCursor(35,60);
 display.setTextColor(GREEN,BLACK);
 display.setTextSize(1);
 display.println("Let's Play");

   for (int i=0; i<10; i++) {
    delay(50);
  }
  
}

void callibrate(sensors_event_t &event)
{
  if(cal_var == 0 ){
   AccelX = event.acceleration.x;
   AccelY = event.acceleration.y;
   AccelZ = event.acceleration.z;
   cal_var = 1;
  }}
  
void loop() {
  /*
  accel.getEvent(&event);
  callibrate(event);
  
  X = event.acceleration.x - AccelX; 
  Y = event.acceleration.y - AccelY; 
  Z = event.acceleration.z - AccelZ;*/

  
  
  int ms = millis();
  sensors_event_t event; 
accel.getEvent(&event);
  X = event.acceleration.x - AccelX;

  if (ms >= nextUpdate && !hasLost()) {
    currentObstacles = generateObstacles();
    paintObstacles();
    nextUpdate = ms + GAME_UPDATE_MS;
  }

  if (ms >= nextBallUpdate) {
    paintBall();
    nextBallUpdate = ms + BALL_UPDATE_MS;
  }

  if (hasLost()) {
    gameOver(event,AccelX);
  }

  //buttonState = digitalRead(BUTTON_PIN);

  buttonState = (X>3);
  
  if (buttonState == 1 && !isInAir()) {
    inAirStart = ms;
  }
}
