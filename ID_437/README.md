#  IITBBS_GC_RS_121
ESPAIN Submission for GC'23
## Problem statement
The problem statement was to build a crytocurrency tracker with ESPAIN and Arduino which is required to be displayed on the LCD display. We were provided with the following components.

1.  *Arduino UNO with Connection cable.
2.  *ESP8266 module
3.  *Color LCD TFT Display
4.  Breadboard
5.  Male2Male Jumper Wires
6.  Male2Female Jumper Wires
7.  Female2Female Jumper Wires The components marked with ‘*’ were mandatory to use in the development.
## Working

First the we are trying to connect to the wifi using an **ESP 8266** , then we are making an API call to **Coin Gecko** , which returns a **JSON** as respons containing the cryptocurrency data . Then we are parsing the **JSON** to extract data. Which is then displayed on the **TFT LCD 144** display screen.
 
## Explaination of UI on TFT
The Screen is divided into two parts :

- The left rectangular part diplays the data of a cryptocurrency like price in usd , price change in 24 hr etc . It the region has a border whose colour is **Red** is the price less than a preset range set by the user , its **Green** its above the range and its **Blue** if its in the range.The display iterates over the 8 cryptocurrency and display them through some time interval.
- The right column displays the status of 8 cryptocurrency . The status is shown by the same colour logic as above.
  
## Files Structure

There are two types of files :

- Testing files
	- ESPdiaplayTest  
	- espTest
- Main files
	- main
	- infoScreen
	- priceTrakerUI


## Libraries used in development
1.  Wire.h
2.  Adafruit_GFX.h
3.  TFT_ILI9163C.h
4.  ESP8266WiFi.h
5.  WiFiClientSecure.h
6.  ESP8266HTTPClient.h
7.  Arduino_Json.h

## Flow of the code
(https://user-images.githubusercontent.com/40049375/229593897-f9c4a291-14c0-4ac1-864c-2a54c8a55b1a.jpeg)
## How to run 

Following are the steps to run the application:

- Install the given Libraries
- Connect the ESP to your device 
- Select the Board a and the port 
- Upload the file main.ino

## Contributors

1.  Aniket Roy
2.  Jatin Yadav
3.  Kumar Saurabh
4.  Manish Kausik Hari Baskar
5.  Shlok Kumar Shaw



  
