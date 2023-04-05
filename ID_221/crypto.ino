/*The code is designed to run on an ESP8266 microcontroller. 
It includes several libraries, such as the Adafruit ST7735 library for driving a small color TFT LCD screen,
the ESP8266WiFi library for connecting to a WiFi network, the ESP8266HTTPClient library for making HTTP requests,
the WiFiClientSecureBearSSL library for secure communication, and the ESP8266WebServer library for handling HTTP requests.
The code initializes the TFT LCD display, sets up the WiFi connection, and sets up an HTTP server on port 80.
The server has two routes: "/" and "/input". The "/" route displays an HTML page with a form for inputting data,
while the "/input" route receives the data sent in the POST request and saves it to the variables initialized in the beginning.
The handleInput() function is responsible for handling the POST request and saving the received data to the variables accessible by other parts of code.
In the main loop of the program, the code waits for input data to be received by checking the "type" variable.
If no data has been filled in the input, the code waits for it by using a goto statement to jump to a label. 
Once the data has been received, It acts upon the user input displaying either the price chart or Table of prices. 
The program sends an HTTP GET request to the Binance API to retrieve the latest price/prices of the needed cryptocurrencies.
The response from the API is displayed on the TFT LCD display according to the program.
Overall, the code sets up an HTTP server that can receive input data and displays the latest cryptocurrency prices
in either table or graph form from the Binance API on an LCD display.*/



//Header files included
#include <Adafruit_ST7735.h>
#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClientSecureBearSSL.h>
#include <ESP8266WebServer.h>
#include <ArduinoJson.h>

// LCD display pin connections
#define TFT_CS     15
#define TFT_RST    3
#define TFT_DC     4
Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_RST);

// Initialisation of Global Variables, Network parameters and Server initialisation
int data[11]={0};
int xc[11] = {10,17,24,31,38,45,52,59,66,73,80}; 
float price=0;
float price2[5] = {0};
int data_index = 0; // data indexing 
const char* ssid = "Replace with your SSID";
const char* password = "Replace with your Password";
String coin[5] = {""};
String type="";
String usd = "USDT";
bool passFlag = 0;
ESP8266WebServer server(80);


void setup() {
  //LCD display & serial monitor initialisation
  Serial.begin(9600);
  tft.initR(INITR_BLACKTAB);
  tft.setRotation(3);
  tft.fillScreen(ST7735_BLACK);

  //connecting ESP8226 to Internet  
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  tft.setCursor(10, 10);
  tft.setTextColor(ST7735_GREEN);
  tft.setTextSize(1);
  tft.print("Connecting to WiFi ..");
  Serial.print("Connecting to WiFi ..");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print('.');
    delay(1000);
  }
  Serial.println("WiFi connected");
  tft.setCursor(10, 20);
  tft.print("WiFi connected");
  tft.setCursor(10, 30);
  Serial.println("IP address: ");
  tft.print("IP address: ");
  Serial.println(WiFi.localIP());
  tft.setCursor(10, 40);
  tft.print(WiFi.localIP());

  // Setup web server routes  
  server.on("/", handleRoot);
  server.on("/input", handleInput);
  server.begin();
  Serial.println("HTTP server started");

}

void loop() {
  // Waiting for the input from the browser
  a:
  server.handleClient();
  if (coin[0] == "" && passFlag == 0) {
    goto a;
  }
  else {
    passFlag = 1;
  }
  // Taking Input whether to show graph of a coin or price table of coins 
  if(type=="1"){
    showGraph(); // Showing graph
  }
  else{
    showList(); // Showing Table
  }
  
}

// Code for displaying the Table of cryptocurrency prices
void showList(){
  int idx=0; 
  // Display coin names on LCD display
  tft.fillScreen(ST7735_BLACK);
  tft.setCursor(10, 5);
  tft.setTextColor(ST7735_GREEN);
  tft.setTextSize(1);
  tft.print("Tracking:");

  tft.setCursor(10, 25);
  tft.setTextColor(ST7735_GREEN);
  tft.setTextSize(1);
  tft.print(coin[0]);
  tft.print(":");  

  tft.setCursor(10, 45);
  tft.setTextColor(ST7735_GREEN);
  tft.setTextSize(1);
  tft.print(coin[1]);
  tft.print(":");  

  tft.setCursor(10, 65);
  tft.setTextColor(ST7735_GREEN);
  tft.setTextSize(1);
  tft.print(coin[2]);
  tft.print(":"); 

  tft.setCursor(10, 85);
  tft.setTextColor(ST7735_GREEN);
  tft.setTextSize(1);
  tft.print(coin[3]);
  tft.print(":"); 

  tft.setCursor(10, 105);
  tft.setTextColor(ST7735_GREEN);
  tft.setTextSize(1);
  tft.print(coin[4]);
  tft.print(":"); 

  // Displaying the prices of the coins
  tft.setCursor(70, 25);
  tft.setTextColor(ST7735_WHITE);
  tft.setTextSize(1);
  tft.print(price2[0]); 

  tft.setCursor(70, 45);
  tft.setTextColor(ST7735_WHITE);
  tft.setTextSize(1);
  tft.print(price2[1]); 

  tft.setCursor(70, 65);
  tft.setTextColor(ST7735_WHITE);
  tft.setTextSize(1);
  tft.print(price2[2]);

  tft.setCursor(70, 85);
  tft.setTextColor(ST7735_WHITE);
  tft.setTextSize(1);
  tft.print(price2[3]);

  tft.setCursor(70, 105);
  tft.setTextColor(ST7735_WHITE);
  tft.setTextSize(1);
  tft.print(price2[4]);

  // Fetching the prices of 5 cryptocurrencies
  while(idx<5 && coin[idx]!=""){
    std::unique_ptr<BearSSL::WiFiClientSecure> client(new BearSSL::WiFiClientSecure);
    client->setInsecure();
    HTTPClient https;
    String urlbase = "https://api1.binance.com/api/v3/ticker/price?symbol=";
    String url = urlbase + coin[idx] + usd;
    //Initializing Data
    String payload="";
    //Retrieving the data
    if (https.begin(*client, url)) {  // HTTPS
      int httpCode = https.GET();
      if (httpCode > 0) {
        Serial.printf("Response code: %d\n", httpCode);
        payload = https.getString();
        
        DynamicJsonDocument doc(1024);
        deserializeJson(doc, payload);
        price2[idx] = doc["price"];
        Serial.println(price2[idx]);
      } else {
        Serial.printf("Error response: %s\n", https.errorToString(httpCode).c_str());
      }
      https.end();
    }
    idx++;
  }

  delay(3000);
}

// Code for displaying the Graph of a cryptocurrency
void showGraph(){
  // Displaying header on LCD display
    tft.fillScreen(ST7735_BLACK);
    tft.setCursor(10, 5);
    tft.setTextColor(ST7735_GREEN);
    tft.setTextSize(1);
    tft.print("Tracking:");
    
    tft.setCursor(90, 5);
    tft.setTextColor(ST7735_GREEN);
    tft.setTextSize(1);
    tft.print(coin[0]);

    // Fetching the price of cryptocoin
    std::unique_ptr<BearSSL::WiFiClientSecure> client(new BearSSL::WiFiClientSecure);
    client->setInsecure();
    HTTPClient https;
    String urlbase = "https://api1.binance.com/api/v3/ticker/price?symbol=";
    String url = urlbase + coin[0] + usd;
    //Initializing Data
    String payload="";
    show(price, payload); // Displaying the Graph
    //Retrieving the data
    if (https.begin(*client, url)) {  // HTTPS
      int httpCode = https.GET();
      if (httpCode > 0) {
        Serial.printf("Response code: %d\n", httpCode);
        payload = https.getString();
        //Extracting the JSON object into float value  
        DynamicJsonDocument doc(1024);
        deserializeJson(doc, payload);
        price = doc["price"];
        Serial.println(price);
        price = round(price);
      } else {
        Serial.printf("Error response: %s\n", https.errorToString(httpCode).c_str());
      }
      https.end();
    }
    delay(2000);
}

// Code for the Graph visualisation
void show(float price, String payload){
  
  // setting the limits for graph on the display
  int xmin=10, xmax=80, ymin=20, ymax=90; 
  tft.drawRect(8, 90, 72, 2, ST7735_YELLOW);
  tft.drawRect(8, 20, 2, 70, ST7735_YELLOW);

  // Updating the data array when new instance of crypto price is fetched  
  if(data[10]!=0)for(int i=1;i<11;i++)data[i-1]=data[i];
  data[data_index] = price;
  Serial.println(data_index);
  data_index = min((data_index+1),10);
  int avg=0,dmin=data[0],dmax=data[0];

  //Serial printing for debugging 
  for(int i=0;i<11;i++){
    Serial.print(data[i]);  
    Serial.print(" ");  
  }

  // limiting the price range in order to display in the graph limits  
  for(int i=0;i<11;i++) {if(data[i]!=0)dmin=min(dmin,data[i]);dmax=max(dmax,data[i]);}
  int plot[11]={0};
  for(int i=0;i<11;i++){
    if(data[i]==0 || dmax==dmin)continue;
    float temp = ((data[i]-dmin)*70)/(dmax-dmin);
    plot[i] = round(temp);
  }

  // Drawing lines between the points   
  for(int i=0;i<11;i++){
    if(plot[i]!=0)tft.drawRect(xc[i], ymax-plot[i], 2, 2, ST7735_RED);
    if(i!=0 && plot[i]!=0)tft.drawLine(xc[i-1], ymax-plot[i-1], xc[i], ymax-plot[i], ST7735_WHITE);
  }

  // Serial printing for debugging
  for(int i=0;i<11;i++)
  Serial.print(plot[i]);

  //Displaying the minimum value
  tft.setCursor(90, 90);
  tft.setTextColor(ST7735_WHITE);
  tft.setTextSize(1);
  tft.print(dmin);

  //Displaying the maximum value
  tft.setCursor(90, 20);
  tft.setTextColor(ST7735_WHITE);
  tft.setTextSize(1);
  tft.print(dmax);
  
  //Displaying the current price  
  tft.setCursor(10, 110);
  tft.setTextColor(ST7735_GREEN);
  tft.setTextSize(1.5);
  tft.print("Price :");
  tft.print(price);
}

// Root page when client hits the server
void handleRoot() {
  // Send a simple HTML page with a form for inputting data
  String html = "<html><body>Enter symbols of crypto in the fields<br>Ex : BTC for Bitcoin<br><br><h2>Enter data:</h2><form action=\"/input\" method=\"post\">Type 1 for Graph and 2 for List of coins:<br><input type=\"text\" name=\"type\"><br><br>Enter the coin Symbol to display graph : <br><input type=\"text\" name=\"coin1\"><br><br>Enter the coin symbol to insert in list : <br><input type=\"text\" name=\"coin2\"><br><br>Enter the coin symbol to insert in list : <br><input type=\"text\" name=\"coin3\"><br><br>Enter the coin symbol to insert in list : <br><input type=\"text\" name=\"coin4\"><br><br>Enter the coin symbol to insert in list : <br><input type=\"text\" name=\"coin5\"><br><br><input type=\"submit\" value=\"Send\"></form></body></html>";
  server.send(200, "text/html", html);
}

//Page when data is entered by the client
void handleInput() {
  // Retrieve the type of the output requested by the client
  if (server.hasArg("type")) {
    String data = server.arg("type");
    Serial.print("Data received: ");
    type = data;
    server.send(200, "text/plain", "Data received: " + data);

  } else {
    server.send(400, "text/plain", "Bad Request");
  }

  //Fetching the input data in coin field 5
  if (server.hasArg("coin1")) {
    String data = server.arg("coin1");
    Serial.print("Data received: ");
    // Serial.println(data);
    coin[0] = data;
    server.send(200, "text/plain", "Data received: " + data);

  } else {
    server.send(400, "text/plain", "Bad Request");
  }
  
  //Fetching the input data in coin field 2
  if(server.hasArg("coin2")){
    String data = server.arg("coin2");
    Serial.print("Data received: ");
    Serial.print(data);
    coin[1]=data;
  } else {
    server.send(400, "text/plain", "Bad Request");
  }

  //Fetching the input data in coin field 3
  if(server.hasArg("coin3")){
    String data = server.arg("coin3");
    Serial.print("Data received: ");
    Serial.print(data);
    coin[2]=data;
  } else {
    server.send(400, "text/plain", "Bad Request");
  }
  
  //Fetching the input data in coin field 4
  if(server.hasArg("coin4")){
    String data = server.arg("coin4");
    Serial.print("Data received: ");
    Serial.print(data);
    coin[3]=data;
  } else {
    server.send(400, "text/plain", "Bad Request");
  }

  //Fetching the input data in coin field 5
  if(server.hasArg("coin5")){
    String data = server.arg("coin5");
    Serial.print("Data received: ");
    Serial.print(data);
    coin[4]=data;
  } else {
    server.send(400, "text/plain", "Bad Request");
  }
}
