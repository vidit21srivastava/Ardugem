#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include <ArduinoJson.h>  // Library used for parsing Json from the API responses
#include <SPI.h>
#include <TFT_eSPI.h>

#define BLACK 0X0000
#define BLACK 0X0000
#define WHITE 0xFFFF
#define BLUE 0x201C
#define RED 0xF800
#define GREEN 0x07E0
#define CYAN 0x07FF
#define YELLOW 0xFFE0

const int name_offset_x_1 = 8,
          name_offset_y_1 = 8,
          line_spacing_1 = 15,
          padding_x_1 = 10;


char ssid[] = "BEAST_OP";       // network SSID (name)
char password[] = "Shlok@*!))";  // network key

WiFiClientSecure client;    // Create a WiFi client object

// Just the base of the URL you want to connect to
#define TEST_HOST "api.coingecko.com"

// #define TEST_HOST_FINGERPRINT "B3 DD 76 06 D2 B5 A8 B4 A1 37 71 DB EC C9 EE 1C EC AF A3 8A"  //    SHA-1
// #define TEST_HOST_FINGERPRINT "3A BB E6 3D AF 75 6C 50 16 B6 B8 5F 52 01 5F D8 E8 AC BE 27 7C 50 87 B1 27 A6 05 63 A8 41 ED 8A"  //    SHA-256

TFT_eSPI display = TFT_eSPI();

const int jsonMaxSize = 384;

void setup() {

  // Serial.begin(115200);


  //initialising display
  display.init();
  display.setRotation(6);
  display.fillScreen(BLACK);
  display.fillRect(2, 1, 128, 128, BLACK);

  //Title Screen
  String title1 = "  Crypto", title2 = "  Tracker", subtitle = "\n   Track all your\n   favourite coins\n   at one place !!";
  display.setTextSize(2);
  display.setCursor( 5 , 20 );
  display.setTextColor(RED);
  display.println(title1);
  display.setTextColor(GREEN);
  display.println(title2);
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.println(subtitle);
  display.fillRect(2,  1, 128,  3, CYAN);
  display.fillRect(2,  4,   3, 123, CYAN);
  display.fillRect(2, 126,128,  3, CYAN);
  display.fillRect(127, 4,  3, 123, CYAN);

  delay(2000);


  // Connect to the WiFI
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(100);

  // Attempt to connect to Wifi network:
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }
  // client.setFingerprint(TEST_HOST_FINGERPRINT);
  client.setInsecure(); //Fingerprint wasn't able to be verified so, we removed the check


  display.fillRect(2, 1, 128, 128, BLACK);  //for clearing screen


    //rendering the UI skeleton

    //displaying coin name
    display.setCursor( name_offset_x_1, name_offset_y_1 );
    display.setTextSize(2);
    display.setTextColor(WHITE);
    display.print("CoinName");


    //displaying price of coin
    display.setCursor( padding_x_1, name_offset_y_1 + 2*line_spacing_1 );
    display.setTextSize(1);
    display.setTextColor(YELLOW);
    display.print("Price:$ ");
    display.setTextColor(WHITE);
    display.print("2000");

    //displaying change in last 24h
    display.setTextColor(YELLOW);
    display.setCursor( padding_x_1, name_offset_y_1 + 3*line_spacing_1 );
    display.print("Last 24h: ");
    display.setTextColor(GREEN);
    display.setTextColor(WHITE);
    display.print("3.04%");
    
    //displaying market cap
    display.setTextColor(YELLOW);
    display.setCursor( padding_x_1, name_offset_y_1 + 4*line_spacing_1 );
    display.print("Market Cap:");
    display.setCursor( padding_x_1, name_offset_y_1 + 5*line_spacing_1 );
    display.setTextColor(WHITE);
    display.print("$ 5000000.00");

    //displaying 24hr volume
    display.setTextColor(YELLOW);
    display.setCursor( padding_x_1, name_offset_y_1 + 6*line_spacing_1 );
    display.print("24h vol:");
    display.setCursor( padding_x_1, name_offset_y_1 + 7*line_spacing_1 );
    display.setTextColor(WHITE);
    display.print("35000.00");



}

DynamicJsonDocument makeHTTPRequest( String request ) {

  DynamicJsonDocument doc(jsonMaxSize);
  // Opening connection to server
  if (!client.connect(TEST_HOST, 443))
  {
    // Serial.println(F("Connection failed"));
    return doc;
  }

  yield();

  // Send HTTP request
  client.print(F("GET "));
  // This is the second half of a request (everything that comes after the base URL)
  client.print( request );
  
  client.println(F(" HTTP/1.1"));

  //Headers
  client.print(F("Host: "));
  client.println(TEST_HOST);

  client.println(F("Cache-Control: no-cache"));

  if (client.println() == 0)
  {
    // Serial.println(F("Failed to send request"));
    return doc;
  }
  // delay(100);

  // Check HTTP status
  char status[32] = {0};
  client.readBytesUntil('\r', status, sizeof(status));
  if (strcmp(status, "HTTP/1.1 200 OK") != 0)
  {
    // Serial.print(F("Unexpected response: "));
    // Serial.println(status);
    return doc;
  }

  // Skiping HTTP headers
  char endOfHeaders[] = "\r\n\r\n";
  if (!client.find(endOfHeaders))
  {
    // Serial.println(F("Invalid response"));
    return doc;
  }

  //to ignore random characters before the json
  while (client.available() && client.peek() != '{')
  {
    char c = 0;
    client.readBytes(&c, 1);
    // Serial.print(c);
    // Serial.println("BAD");
  }

  DeserializationError error = deserializeJson(doc, client);

  if (!error) return doc; 
  
  else {
    // Serial.print(F("deserializeJson() failed: "));
    // Serial.println(error.f_str());
    return doc;
  }
}

String coin_dat3[]= {"Bitcoin  ","Ethereum ","Tether   ","Binance  ","USD Coin ","Ripple   ","Cardano  ","Dogcoin  "};
String coin_codes[]= {"bitcoin","ethereum","tether","binancecoin","usd-coin","ripple","cardano","dogcoin"};

String request1_1 = "/api/v3/simple/price?ids=";
String request1_2 = "&vs_currencies=usd&include_market_cap=true&include_24hr_vol=true&include_24hr_change=true";
String request2 = "/api/v3/simple/price?ids=bitcoin%2Cethereum%2Ctether%2Cbinancecoin%2Cripple%2Cusd-coin%2Ccardano%2Cdogecoin&vs_currencies=usd";

void loop() {
  // put your main code here, to run repeatedly:

  for(int i=0;i<8;i++){

    DynamicJsonDocument doc1(jsonMaxSize) ;
    DynamicJsonDocument doc2(jsonMaxSize) ;
    doc1 = makeHTTPRequest( request1_1 + coin_codes[i] + request1_2);
    doc2 = makeHTTPRequest(request2);

    delay(4000);

    infoScreen( doc1, display, coin_dat3[i], i );
    priceTraker(doc2, display, i);
    
  }

}