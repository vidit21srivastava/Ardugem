# Crypto Tracker with ESP8266
 This project demonstrates how to track cryptocurrency prices using an ESP8266
microcontroller and an LCD display. The microcontroller fetches cryptocurrency price data from the
Binance API and displays it on the LCD screen.
## Components used
 • ESP8266 microcontroller
 
 • 1.44inch 128*128 ST7735S LCD display
 
 • Jumper wires
 
 * optional Components
 
 • potentiometer (to adjust the brighness of Backlight)
 
 • Lipo Battery & charge controller
 
## Prerequisites
 • Arduino IDE
 
 • Wi-Fi network
 
 • Binance API Key
 
## Setup
### Hardware setup
1. Connect the ST7735 LCD display to the ESP8266 microcontroller. The connections are as
follows:
 ◦ SCK to GPIO14
 
 ◦ MOSI to GPIO13
 
 ◦ CS to GPIO15
 
 ◦ RST to GPIO3
 
 ◦ DC to GPIO4
 
 ◦ VCC to 3.3V
 
 ◦ GND to GND
 
* Connections for optional features


 ◦ Potentiometer pin-1&3 to 3V3 & GND, slider pin to LED
 
 ◦ Follow circuit diagram for connecting battery and charge controller.
 
### Software setup
1. Install the following libraries in the Arduino IDE:

 ◦ Adafruit_ST7735.h
 
 ◦ ArduinoJson.h
 
 ◦ ESP8266WiFi.h
 
 ◦ ESP8266HTTPClient.h
 
 ◦ ESP8266WebServer.h
 
 ◦ WiFiClientSecureBearSSL.h
 
2. Upload the code to the ESP8266 microcontroller.
3. Connect the ESP8266 to a Wi-Fi network. Enter the SSID and password of the network in the
ssid and password variables in the code.
4. Start the HTTP server on the ESP8266 microcontroller by calling server.begin().
5. Open a web browser and enter the IP address of the ESP8266 microcontroller to access the web
server

## Usage
1. Enter whether you want to look at the price history chart of a cryptocurrency or to view the list of prices of 
five cryptocurrencies simultaneously
2. If entered "1" in the type field, price history chart of first coin will be displayed
3. If entered "2" in the type field, List of the prices of the 5 crypto coins will be tracked in real time
4. The ESP8266 microcontroller will fetch the cryptocurrency price data whenever needed from the Binance API and
display it on the LCD screen.

## Limitations
 • The ESP8266 microcontroller has limited processing power, so it may not be able to handle
large amounts of data.

 • The Binance API has rate limits that may affect the performance of the application.
## Acknowledgments
 • The Binance API was used to fetch the cryptocurrency price data.
 
 • The Adafruit_ST7735 library was used to interface with the LCD display.
 
 • The ArduinoJson library was used to parse the JSON data from the API response.
