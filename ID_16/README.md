


####Introduction of Project
This is an implementation of a simple game from a popular gaming genre called Platformers inspired by classic games like Super Mario or Gianna Sisters. This is the project made using Adafruit_GFX and Adafruit_ST7735 libraries for display and Wire.h for accelerometer. In this game, player controls a character who jumps by sensor movement and crosses the obstacles. The game goes on endlessly and the game is over when character collide with obstacle coming in its way.

<br>
<br>

####Components used
-  Arduino UNO
-  TFT ILI9163C LCD SCREEN 1.44' using ST7755 display driver
-  Accelerometer
-  Breadboard 
-  Male to Male, Male to Female Jumper Wires
-  USB Cable



<br>



####Setup

It will work in any Operating System with Arduino IDE but you have to install sprecified libraries in your Arduino IDE which may not be pre-installed.

EXTERNAL LIBRARIES
These are the libraries that you need to install
- Adafruit_GFX.h Library
- Adafruit_ST7735.h  (On Arduino IDE available as AdaFruit ST7735 and ST7739 library)
- Wire.h library

<br>

####Connections
Pin Congiguration:
######TFT Display with Arduino
A0: D9
CS: D10
SDA: D11
RESET: D12
SCK: D13
LED: 3.3V
VCC: 5V
GND: GND

######Accelerometer with Arduino
VCC: 3.3V
GND: GND
SDA: A4
SCL: A5

 
<br>





####Installation Guide
After downloading Arduino IDE on your system, download all the required libraries in your Arduino IDE. Now copy-paste the code of the gc_robotics on your Arduino IDE. 

Now after doing connections as shown, upload the code to the Arduino board. Now the game will be started.

<br>

####Playing Game
- The game starts with the initial screen displaying "" and then after loading main screen appears.
- Now the character appears at left of screen.
- The obstacles start coming on the screen towars the player.
- The player controls the character by accelerometer. As the accelerometer is lifted up, the charcter jumps.
- If the character collides with the obstacle, the game ends.

