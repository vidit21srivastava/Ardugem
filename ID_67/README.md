# ARDUGEM: GAME THEME
Teams have to develop a game under a popular gaming genre called Platformers. Platform games
(or platformers) have gameplay primarily centered around jumping and climbing to navigate the
player's environment. They may have enemies or obstacles to avoid and fight or may just be pure
jumping puzzles. Generally, the playable character in a platform game can jump many times their
height, and the player is offered some control over their movement in mid-air as well as the height
and distance of their jumps Settings tend to be vertically exaggerated with much uneven terrain that
the player can leap up to or fall off of.

The game should also have a scoring mechanism.
Teams have to give a name to their game.
Teams are provided with a kit containing the following:
1. *Arduino UNO with Connection cable.
2. *ADXL345 Accelerometer
3. *Color LCD TFT Display
4. Breadboard
5. Male2Male Jumper Wires
6. Male2Female Jumper Wires
7. Female2Female Jumper Wires
• Further, teams could request for resistors and capacitors if required.
• The components marked with ‘*’ are mandatory to use in the development.
• Teams are allowed to use their personal components.

Key Challenges:
• Storage Space: Arduino boards come with minimal RAM or flash memory. Not only does this
limit the amount of code they can run, but it also presents challenges when it comes to working
with variables.
• Processing Power: The Arduino we used has a low-power CPU, so creating resource-hungry
applications is impossible.
• Components: The game must incorporate accelerometer-based controls.


# DINO RUN

This is an Arduino game project that involves creating a simple game called Dino Run using the
Adafruit_GFX and Adafruit_ST7735 libraries for the TFT display and the ADXL345_Unified
library for the accelerometer. The player controls dinosaur and must jump over obstacles or other
dinosaur’s to avoid collision while advancing through the game. The score increases as the player
collects the coins and the game ends if the player collides with any obstacles or other dinosaur. The
game board also has extra features like Backlight Brightness adjustment, sound effects and the
game board can be USB powered or battery powered.
## Components Used

• Arduino UNO board

• 1.44inch SPI Module MSP1443 using ST7735S display driver

• ADXL345 I2C & SPI based accelerometer (used I2C in this project)

• Breadboard

• Jump wires /Hook wires

Optional components:

• Li-po battery

• Li-po charge discharge module

• 10K potentiometer

• 100Ω Resistor

• Small speaker

* if Low impedance speaker is used then add a sufficient series resistor to limit the max current drawing from the Digital pin

## Library Required
• Wire.h

• Adafruit_GFX.h

• Adafruit_ST7735.h

• Adafruit_ADXL345_U.h

## Installation
1. Download and install the Arduino IDE.
2. Connect the Arduino board to the computer using a USB cable.
3. Open the Arduino IDE and select the correct board and port.
4. Download the required libraries.
5. Copy the code and paste it into the Arduino IDE.
6. Upload the code to the Arduino board.
7. Connect the TFT display and the accelerometer to the Arduino board according to the pin configuration.
8. Power up the Arduino board.
9. The game should start automatically

## Pin Configuration
Accelerometer:

 • SDA: A4

 • SCL: A5

 • VCC: 3.3V

 • GND: GND


LCD Display:

 • CS: D10

 • RST: D9

 • DC: D8

 • MOSI: D11

 • SCK: D13

 • LED: 3.3V

 • VCC: 5V

 • GND: GND

 Optional connections for Brightness adjustment and External battery power

• A0 -----> potentiometer mid pin (wiper pin)

• Potentiometer -----> 5V & GND (end pins)

• A1 -----> Battery(+ve)

* Refer circuit diagram for more detailes

## How To Play

 • The game starts with the dinosaur at the left of the screen.

 • The player controls the dinosaur with the accelerometer.

 • If the accelerometer's y-value is greater than 5.0, the dinosaur jumps.

 • The dinosaur must jump over obstacles to avoid collision and advance through the game.

 • The score increases as the player progresses.

 • The game ends if the dinosaur collides with any obstacle.
 
 • If game is over tilting it upward restarts the game.
