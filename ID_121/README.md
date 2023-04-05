# ID_121
# Components used-ESP8266 nodemcu module, TFT LCD 1.44'' display 

<br/>

# Circuit Diagram 
![Circuit diagram](https://user-images.githubusercontent.com/66817144/229369494-22d983ad-b916-4cd2-85aa-7c9109589269.png)



ESP8266 needs to be connected to laptop (using USB to micro USB type-B cable) and the arduino file needs to be run in the arduino IDE

# Connections 
TFT LCD display| ESP8266 nodemcu  <br/>
             VCC---------------------3V3<br/>
             GND---------------------GND<br/>
             CS----------------------D2<br/>
             RST---------------------D3<br/>
             AO----------------------D4<br/>
             SDA---------------------D7<br/>
             SCK---------------------D5<br/>
             LED---------------------3V3<br/>
             

# Structure of the files

CryptoAPI folder- an API made in Nodejs to get the statistics of crypto currencies from Binance 
api_design.ino(IDE used-Arduino IDE )- code file written in arduino for displaying CRYPTO TRACKER 


# Overview of how the code works
A custom API is deployed with the name "http://cryptodosth.com/api/statistics?symbol=ETHUSDT" which is made to get particular details about crypto currencies from Binance API . 
When the arduino file is run, ESP8266 nodemcu module connects with wifi and makes a get request to this custom API. Further this data is displayed on LCD TFT display with every 1 seconds.

# Instructions to run the code
Make the connections shown above.<br/>
Install Arduino IDE in your laptop. <br/>
Change the SSID and password of your wifi network to connect with the particular wifi.<br/>
If wifi is connected, it shows this message "Connected".<br/>
When wifi is disconnected, it shows this message "Disconnected".<br/>
Run the arduino code file.<br/>
Then the crypto tracker gets displayed<br/>

# Block diagram of code
![block diagram](https://user-images.githubusercontent.com/66817144/229369240-17f25b15-0a90-4b81-b6f1-95d6f5821b53.png)

# Libraries used
1.	Adafruit ST7735:  used to control the tft display.<br/>
2.	ESP8266WiFi - a library that can give any microcontroller access to your WiFi network.<br/>
3.	ESP8266HTTPClient - a library used to make HHTP requests.<br/>
4.	WifiClientSecure-It is a library that extends WiFiClient which can be used with minimal changes to code that does unsecured communications.<br/>
5.	WiFiClient<br/>
6.	ArduinoJson<br/>
7.	WiFiClientSecure<br/>



