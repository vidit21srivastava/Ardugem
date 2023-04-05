
#include <Adafruit_ST7735.h>   // include Adafruit ILI9341 TFT library
#include <ESP8266WiFi.h>       // include ESP8266 WiFi library
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
#include <ArduinoJson.h>
#include <WiFiClientSecure.h>

#define TFT_CS    D2     // TFT CS  pin is connected to NodeMCU pin D2
#define TFT_RST   D3     // TFT RST pin is connected to NodeMCU pin D3
#define TFT_DC    D4     // TFT DC  pin is connected to NodeMCU pin D4
// initialize ILI9341 TFT library with hardware SPI module
// SCK (CLK) ---> NodeMCU pin D5 (GPIO14)
// MOSI(DIN) ---> NodeMCU pin D7 (GPIO13)
Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_RST);

//Network login credentials
const char* ssid     = "helloboi";
const char* password = "dmidmidmi";

void draw_border(){
  tft.fillScreen(ST7735_BLACK);
  int16_t x1 = 0;
  int16_t y1 = 0;
  int16_t x2 = tft.width() - 1;
  int16_t y2 = tft.height() - 1;
  tft.drawRect(x1, y1, x2 - x1, y2 - y1, ST7735_WHITE);
}

void WifiStatusScreenBackground(){
  //Clear the screen first
  tft.fillScreen(ST7735_BLACK);
  draw_border();
  //display heading
  tft.setCursor(30,10);
  tft.setTextColor(ST7735_YELLOW);
  tft.setTextSize(1);
  tft.println("WiFi Status");
  //display underline for heading
  tft.drawLine(20,21,105,21,ST7735_RED);
}

void WifiStatusScreenForeground(String wifistatus){
  //display the font in middle of the screen
  tft.setCursor(35,60);
  tft.setTextColor(ST7735_WHITE);
  tft.setTextSize(0.9);
  tft.println(wifistatus);
}

//API essentials
const char* ada_api = "http://cryptodosth.com/api/statistics?symbol=ADAUSDT";
const char* bnb_api = "http://cryptodosth.com/api/statistics?symbol=BNBUSDT";
const char* btc_api = "http://cryptodosth.com/api/statistics?symbol=BTCUSDT";
const char* xrp_api = "http://cryptodosth.com/api/statistics?symbol=XRPUSDT";
const char* eth_api = "http://cryptodosth.com/api/statistics?symbol=ETHUSDT";
WiFiClient wificlient;


String get_details(const char* api){
  HTTPClient http;
  http.begin(wificlient,api);
  String payload = "no_data";
  int httpCode = http.GET();
  if (httpCode == HTTP_CODE_OK) {
    payload = http.getString();
    http.end();
    return payload;
  }
  http.end();
  return payload;
}


void display_details(){
  //Get details of all coins first
  String coin1 = get_details(btc_api);
  delay(50);
  String coin2 = get_details(eth_api);
  delay(50);
  String coin5 = get_details(bnb_api);
  delay(50);
  String coin3 = get_details(ada_api);
  delay(50);
  String coin4 = get_details(xrp_api);
  delay(50);

  String c1=String(coin1.substring(0,coin1.indexOf("&")).toFloat(),1); 
  String c2=String(coin2.substring(0,coin2.indexOf("&")).toFloat(),2); 
  String c3=String(coin3.substring(0,coin3.indexOf("&")).toFloat(),5); 
  String c4=String(coin4.substring(0,coin4.indexOf("&")).toFloat(),5); 
  String c5=String(coin5.substring(0,coin5.indexOf("&")).toFloat(),3);

  String d1=String(coin1.substring(coin1.indexOf("&")+1).toFloat(),2);
  if(d1.charAt(0)!='-'){
    d1 = "+"+d1;
  }
  String d2=String(coin2.substring(coin2.indexOf("&")+1).toFloat(),2);
  if(d2.charAt(0)!='-'){
    d2 = "+"+d2;
  } 
  String d3=String(coin3.substring(coin3.indexOf("&")+1).toFloat(),2); 
  if(d3.charAt(0)!='-'){
    d3 = "+"+d3;
  }
  String d4=String(coin4.substring(coin4.indexOf("&")+1).toFloat(),2);
  if(d4.charAt(0)!='-'){
    d4 = "+"+d4;
  }
  String d5=String(coin5.substring(coin5.indexOf("&")+1).toFloat(),2); 
  if(d5.charAt(0)!='-'){
    d5 = "+"+d5;
  }
      
  //Flush the screen of the subpart from 
  tft.fillRect(30, 43, 115, 115, ST7735_BLACK);
  //Display the Heading
  tft.setCursor(10,10);
  tft.setTextColor(ST7735_YELLOW);
  tft.setTextSize(1);
  tft.println("Crypto Dashboard");
  //display underline for heading
  tft.drawLine(5,21,115,21,ST7735_RED); 
  
  tft.setCursor(3,27);
  tft.setTextColor(ST7735_BLUE);
  tft.setTextSize(1);
  tft.println("Coin| Cost($)| %24hr");  

  //Display first line of coin
  tft.setCursor(3,43);
  tft.setTextSize(1);
  if(d1.charAt(0)=='-'){
    tft.setTextColor(ST7735_RED);
  }else{
    tft.setTextColor(ST7735_GREEN);
  }
  tft.println("BTC |$"+c1+"|"+d1+"%");

  tft.setCursor(3,63);
  tft.setTextColor(ST7735_WHITE);
  tft.setTextSize(1);
  if(d2.charAt(0)=='-'){
    tft.setTextColor(ST7735_RED);
  }else{
    tft.setTextColor(ST7735_GREEN);
  }
  tft.println("ETH |$"+c2 +"|"+d2+"%");

  tft.setCursor(3,82);
  tft.setTextSize(1);
  if(d5.charAt(0)=='-'){
    tft.setTextColor(ST7735_RED);
  }else{
    tft.setTextColor(ST7735_GREEN);
  }
  tft.println("BNB |$"+c5 +"|"+d5+"%");
  
  tft.setCursor(3,100);
  tft.setTextSize(1);
  if(d3.charAt(0)=='-'){
    tft.setTextColor(ST7735_RED);
  }else{
    tft.setTextColor(ST7735_GREEN);
  }
  tft.println("ADA |$"+c3+"|"+d3+"%");

  
  tft.setCursor(3,117);
  tft.setTextSize(1);
  if(d4.charAt(0)=='-'){
    
    tft.setTextColor(ST7735_RED);
  }else{
    tft.setTextColor(ST7735_GREEN);
  }
  tft.println("XRP |$"+c4+"|"+d4+"%");

  Serial.println("Working..");
  delay(2000);
  //Now display market cap
  //Flush the screen of the subpart from previous screen
  tft.fillRect(30, 43, 115, 115, ST7735_BLACK);
}


void HomeScreen(){
  //Clear the screen
  tft.fillScreen(ST7735_BLACK);
  draw_border();

  //Heading of the Screen
  tft.setCursor(43, 25);
  tft.setTextColor(ST7735_BLUE);
  tft.setTextSize(1);
  tft.println("Welcome");

  //Middle text
  tft.setCursor(55,55);
  tft.setTextColor(ST7735_BLUE);
  tft.setTextSize(1);
  tft.println("To");

  //Last text
  tft.setCursor(22,90);
  tft.setTextColor(ST7735_BLUE);
  tft.setTextSize(1);
  tft.println("Crypto-Tracker");

  //Display this welcome message for 2 seconds and proceed to coin_display screen
  delay(2000);
  tft.fillScreen(ST7735_BLACK);
  //draw_border();
  //display_details();
}

void establish_connection(){
  WiFi.begin(ssid, password);
  //set wifi dashboard screen
  WifiStatusScreenBackground();
  WifiStatusScreenForeground("Searching");
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(2000);
  }

  //If the wifi is connected, set background and update foreground 
  WifiStatusScreenBackground();
  WifiStatusScreenForeground("Connected");
  //delay this state for 2 sec and start welcome screen
  delay(2000);
  //As soon as the network is connected, display main screen using some animation
  HomeScreen();
}

void setup() {
  //start communication
  Serial.begin(9600);

  //Init with GreenTab
  tft.initR(INITR_144GREENTAB);

  //test functions
  establish_connection();
  //delay(5000);
}


void loop() {
  //Check for wifi connection every time 
  //IF disconnected
  if(WiFi.status() != WL_CONNECTED){
    //launch wifistatusbackground 
    WifiStatusScreenBackground();
    WifiStatusScreenForeground("Disconnected");
    //retry after 5 sec
    delay(5000);
    establish_connection();    
  }else{
    display_details();
    //delay(1000);
  }
  Serial.println("Working..");
}
